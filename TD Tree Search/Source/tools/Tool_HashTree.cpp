//include header
#include "Tool_HashTree.hpp"

/**
Constructor for HashTree

@param maxTreeSizeGB Maximum allowed size of tree in memory (in gigabytes)
@param sizeHashMap Number of entries in the hashMap
*/
HashTree::HashTree(double maxTreeSizeMB, int sizeHashMap)
{
	this->is_initialized = false;
	this->is_allocated = false;
	Init(maxTreeSizeMB, sizeHashMap);
}

//destructor
HashTree::~HashTree(void)
{
	Clear_Memory();
}

//intialization
void HashTree::Init(double maxTreeSizeGB, int sizeHashMap)
{
	this->treeMaxMemorySize = (maxTreeSizeGB * (1 << 20));	//maximum allowed tree size in Bytes
	this->hashMapSize = sizeHashMap;
	this->numAllocNodes = 0;
	this->allocMemorySize = 0.0;
	this->memory_exceeded = false;
	this->root = NULL;
	this->is_initialized = true;
	Reset();
}

//reset
void HashTree::Reset()
{
	//delete/free entire structure
	Clear_Memory();
	Allocate_Memory();
}

void HashTree::Allocate_Memory()
{
	if (this->hashMapSize > 0){
		hashMap = new TreeNode*[hashMapSize];
		for (int h = 0; h < hashMapSize; h++)
			hashMap[h] = NULL;
	}
	this->is_allocated = true;
}

void HashTree::Clear_Memory()
{
	if (is_allocated)
	{
		if (this->hashMapSize > 0){
			for (int h = 0; h < hashMapSize; h++){
				if (hashMap[h] != NULL){
					Delete_Single_HashNode(hashMap[h]);
					hashMap[h] = NULL;
				}
			}
			delete(hashMap);
		}
		else{
			Delete_Branch(this->root);
		}
	}
	this->is_allocated = false;
	this->memory_exceeded = false;
	this->root = NULL;
	this->treeDepth = 0;

	if ((this->numAllocNodes != 0) || (this->allocMemorySize != 0))
		gmp->Print("ERROR: HashTree::Clear_Memory() : tree incorrectly deleted : remaining nodes %d, remaining memory size %.0f [B]\n", this->numAllocNodes, this->allocMemorySize);
}

HashTree::TreeNode* HashTree::Get_State_ActionID(TreeNode* state, int actionID)
{
	TreeNode* newNode = NULL;

	//if transpositions are being used, then do not delete any part of the tree and don't even change the root
	if (this->hashMapSize > 0){
		newNode = Find_Child_ActionID(state, actionID);
	}
	else{
		newNode = Crop_Tree_ActionID(actionID);	//starts from the root, releases memory, changes the root
	}

	return newNode;
}

HashTree::TreeNode* HashTree::Find_Child_ActionID(TreeNode* node, int actionID)
{
	TreeNode* foundChild = NULL;
	if (node != NULL){
		if (node->children != NULL)
		{
			for (int c = 0; c < node->num_children; c++){

				TreeNode* child = node->children[c];
				if (child != NULL){
					if (child->data->actionID == actionID){
						foundChild = child;
					}
				}
			}
		}
	}
	return foundChild;
}

/**
Delete parts of the tree that do not correspond to actionID. Changes the root.
Warning: DO NOT use if the TREE is actually a GRAPH (may delete too much of it)

@return Returns the remaining part of the tree (the child that corresponds to actionID), if there is any
*/
HashTree::TreeNode* HashTree::Crop_Tree_ActionID(int actionID)
{
	if (hashMapSize > 0){
		gmp->Print("ERROR: HashTree::Crop_Tree_ActionID() : tree must NOT be cropped if transpositions are in use (tranpositions table length %d)", this->hashMapSize);
		return NULL;
	}

	TreeNode* remainingBranch = NULL;
	TreeNode* node = this->root;
	int foundMultipleSame = 0;
	if (node != NULL){
		if (node->children != NULL)
		{
			for (int c = 0; c < node->num_children; c++){

				TreeNode* child = node->children[c];
				if (child != NULL){
					if (child->data->actionID != actionID){
						Delete_Branch(child);
					}
					else{
						if (foundMultipleSame == 0){
							remainingBranch = child;
							remainingBranch->parent = NULL;
							remainingBranch->in_parent_seq_index = -1;
							foundMultipleSame++;
						}
						else{
							gmp->Print("ERROR: HashTree::Crop_Tree_ActionID() : multiple nodes with same actionID found - critical BUG in tree building code : actionID %d, numEqual %d", actionID, foundMultipleSame);
							Delete_Branch(child);
						}
					}
				}
			}
		}
		Delete_Single_TreeNode(node);
		this->root = remainingBranch;
	}
	
	if (remainingBranch == NULL)
		this->treeDepth = 0;
	else
		this->treeDepth--;

	return remainingBranch;
}

//deletes specified node and all structures that point from the current node (all children recursively)
void HashTree::Delete_Branch(TreeNode* node)
{
	if (node != NULL){
		if (node->colorTag == NODE_COLORTAG_INITIAL){

			node->colorTag = NODE_COLORTAG_PENDINGDELETE;
			if (node->children != NULL){
				for (int c = 0; c < node->num_children; c++)
					Delete_Branch(node->children[c]);
				delete[] node->children;
				delete[] node->childrenActions;
				this->allocMemorySize -= (node->num_children * sizeof(TreeNode*));
			}
			if (node->data != NULL){
				delete (node->data);
				this->allocMemorySize -= sizeof(StateActionRecord);
			}
			if (node->parent != NULL){
				node->parent->children[node->in_parent_seq_index] = NULL;
			}
			delete node;

			this->allocMemorySize -= sizeof(TreeNode);
			this->numAllocNodes--;

		}
	}
}

//warning: does not free children nodes, for that use HashTree::Delete_Branch()
void HashTree::Delete_Single_TreeNode(TreeNode* node)
{
	if (node->children != NULL){
		delete[] node->children;
		delete[] node->childrenActions;
		this->allocMemorySize -= (node->num_children * sizeof(TreeNode*));
	}
	if (node->data != NULL){
		delete (node->data);
		this->allocMemorySize -= sizeof(StateActionRecord);
	}
	if (node->parent != NULL){
		node->parent->children[node->in_parent_seq_index] = NULL;
	}
	delete node;
	this->allocMemorySize -= sizeof(TreeNode);
	this->numAllocNodes--;
}

//warning: does not set pointers in parents to NULL, should be used only when erasing entire hash table
void HashTree::Delete_Single_HashNode(TreeNode* node)
{
	if (node->children != NULL){
		delete[] node->children;
		delete[] node->childrenActions;
		this->allocMemorySize -= (node->num_children * sizeof(TreeNode*));
	}
	if (node->data != NULL){
		delete (node->data);
		this->allocMemorySize -= sizeof(StateActionRecord);
	}
	delete node;
	this->allocMemorySize -= sizeof(TreeNode);
	this->numAllocNodes--;
}

HashTree::TreeNode::TreeNode()
{
	this->colorTag = NODE_COLORTAG_INITIAL;
}

void HashTree::Output_HashTable(char* printLinePrefix)
{
	if (printLinePrefix == NULL)
		printLinePrefix = "HTAB    ";

	gmp->Print("\n%s", printLinePrefix); gmp->Print("HashTableLength    %d", this->hashMapSize);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("numAllocNodes      %d", this->numAllocNodes);
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("\n%s", printLinePrefix);

	int labelIndex;

	// first output line (hashKey)
	labelIndex = 7;
	gmp->Print("%s  ", TreeNodeAtrLabels[labelIndex]);
	for (int h = 0; h < hashMapSize; h++){
		gmp->Print(TreeNodeAtrFormat[labelIndex], h);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	// second output line (actionID) outputs NULL if node not yet initialized
	labelIndex = 1;
	gmp->Print("%s  ",StateActionAtrLabels[labelIndex]);
	for (int h = 0; h < hashMapSize; h++){
		if (hashMap[h] == NULL)
			gmp->Print("    NULL");
		else
			gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->data->actionID);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	// second output line (actionID) outputs NULL if node not yet initialized
	labelIndex = 1;
	gmp->Print("%s  ", "statePtr");
	for (int h = 0; h < hashMapSize; h++){
		if (hashMap[h] == NULL)
			gmp->Print("        ");
		else
			gmp->Print("%p", hashMap[h]);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	// custom output line
	labelIndex = 0;
	gmp->Print("%s  ", TreeNodeAtrLabels[labelIndex]);
	for (int h = 0; h < hashMapSize; h++){
		if (hashMap[h] == NULL)
			gmp->Print("       .");
		else
			gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->num_children);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	// custom output line
	labelIndex = 2;
	gmp->Print("%s  ", StateActionAtrLabels[labelIndex]);
	for (int h = 0; h < hashMapSize; h++){
		if (hashMap[h] == NULL)
			gmp->Print("       .");
		else
			gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->data->num_visited_total);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	// custom output line
	labelIndex = 16;
	gmp->Print("%s  ", StateActionAtrLabels[labelIndex]);
	for (int h = 0; h < hashMapSize; h++){
		if (hashMap[h] == NULL)
			gmp->Print("       .");
		else
			gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->data->num_visited_episodes);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	// custom output line
	labelIndex = 3;
	gmp->Print("%s  ", StateActionAtrLabels[labelIndex]);
	for (int h = 0; h < hashMapSize; h++){
		if (hashMap[h] == NULL)
			gmp->Print("       .");
		else
			gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->data->Q_value);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	// custom output line
	labelIndex = 13;
	gmp->Print("%s  ", StateActionAtrLabels[labelIndex]);
	for (int h = 0; h < hashMapSize; h++){
		if (hashMap[h] == NULL)
			gmp->Print("       .");
		else
			gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->data->last_estimated_value);
		gmp->Print(" ");
	}
	gmp->Print("\n%s", printLinePrefix);

	//// custom output line
	//labelIndex = 5;
	//gmp->Print("%s  ", StateActionAtrLabels[labelIndex]);
	//for (int h = 0; h < hashMapSize; h++){
	//	if (hashMap[h] == NULL)
	//		gmp->Print("    .");
	//	else
	//		gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->data->maxKnownTargetValue);
	//	gmp->Print(" ");
	//}
	//gmp->Print("\n");

	//// custom output line
	//labelIndex = 6;
	//gmp->Print("%s  ", StateActionAtrLabels[labelIndex]);
	//for (int h = 0; h < hashMapSize; h++){
	//	if (hashMap[h] == NULL)
	//		gmp->Print("    .");
	//	else
	//		gmp->Print(StateActionAtrFormat[labelIndex], hashMap[h]->data->minKnownTargetValue);
	//	gmp->Print(" ");
	//}
	//gmp->Print("\n");
}

void HashTree::Output_Tree(char* printLinePrefix, int compare_episode, int output_depth)
{
	if (printLinePrefix == NULL)
		printLinePrefix = "TREE    ";

	gmp->Print("\n%s", printLinePrefix); gmp->Print("   TreeDepth    %d", this->treeDepth);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("TreeNumNodes    %d", this->numAllocNodes);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("    TreeSize    %.0f MB (max %.0f MB)", (this->allocMemorySize / 1024.0 / 1024.0), (this->treeMaxMemorySize / 1024.0 / 1024.0));
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("\n%s", printLinePrefix);
	if (output_depth >= 0)
		gmp->Print("!! WARNING: tree output depth set to %d !!", output_depth);
	gmp->Print("\n%s", printLinePrefix);
	Output_TreeBranch(this->root, 0, printLinePrefix, compare_episode, output_depth);
}

void HashTree::Output_TreeBranch(TreeNode* node, int depth, char* printLinePrefix, int compare_episode, int output_depth)
{
	if ((output_depth < 0) || (depth <= output_depth)){

		if (printLinePrefix == NULL)
			printLinePrefix = "BRNC    ";

		static const int detailOffsetMaxDepth = 10;

		int detailOffset = this->treeDepth;
		if (detailOffset > detailOffsetMaxDepth)
			detailOffset = detailOffsetMaxDepth;

		if (node != NULL){

			for (int i = 0; i < depth; i++)
				gmp->Print(" .");
			gmp->Print("% 2d   ", node->data->actionID);
			for (int i = 0; i < (detailOffset * 2 - depth * 2); i++)
				gmp->Print(" ");
			gmp->Print(" ->  ");
			Output_SingleNode_LineStats(node);
			if (node->data->created_episode == compare_episode)
				gmp->Print("<- NEW");
			gmp->Print("\n%s", printLinePrefix);

			// recursive call
			for (int c = 0; c < node->num_children; c++)
				Output_TreeBranch(node->children[c], depth + 1, printLinePrefix, compare_episode, output_depth);

		}

	}
}

void HashTree::Output_SingleNode_LineStats(TreeNode* node)
{
	if (node != NULL){
		gmp->Print("action=% d  ", node->data->actionID);
		gmp->Print("statePtr=%p  ", node);
		gmp->Print("hash=%d  ", node->hashKey);
		gmp->Print("nChild=%d  ", node->num_children);
		gmp->Print("visitTot=%.1f  ", node->data->num_visited_total);
		gmp->Print("visitEpi=%.1f  ", node->data->num_visited_episodes);
		gmp->Print("Qval=% .3f  ", node->data->Q_value);
		gmp->Print("estVal=% .3f  ", node->data->last_estimated_value);
		gmp->Print("simMov=%d  ", node->data->created_simulatedGameStep);
		gmp->Print("creEpi=%d  ", node->data->created_episode);
	}
	else{
		gmp->Print("NULL");
	}
}

//static structures
const std::string HashTree::class_name = "HashTree";
const char * const HashTree::TreeNodeAtrLabels[] = {
	"numChild",		//0 number of children
	"  parent",		//1 
	"children",		//2 array of chilren
	"childAct",		//3 array of child actions
	"inParInd",		//4 in parent's child array this node's index
	"    data",		//5
	"colorTag",		//6
	" hashKey"		//7
};
const char * const HashTree::TreeNodeAtrFormat[] = {
	"%8d",
	"%8p",
	"%8p",
	"% 8d",
	"%8d",
	"%8p",
	"%8d",
	"%8d",
};
const char * const HashTree::StateActionAtrLabels[] = {
	" INVALID",		//0
	"actionID",		//1
	"visitTot",		//2  total number of visits (may update multiple times per episode if transpositions are used)
	" Q_value",		//3
	"ZtracTag",		//4
	"maxValue",		//5
	"minValue",		//6
	"crExtPly",		//7  creation timestamp: external game ply
	"creEpiso",		//8  creation timestamp: total episode number
	"crSimPly",		//9  creation timestamp: simulated game ply
	"viExtPly",		//10 last visit timestamp: external game ply
	"visEpiso",		//11 last visit timestamp: total episode number
	"viSimPly",		//12 last visit timestamp: simulated game ply
	"estValue",		//13 estimated value
	"onPchldI",		//14 on policy child index
	"ofPchldV",		//15 off policy child value
	"visByEpi",		//16 number of episodes when the state was visited (visit counter that updates only once per episode)
};
const char * const HashTree::StateActionAtrFormat[] = {
	"%8d",
	"% 8d",
	"%8.1f",
	"% 8.3f",
	"% 8d",
	"% 8.3f",
	"% 8.3f",
	"%8d",
	"%8d",
	"%8d",
	"%8d",
	"%8d",
	"%8d",
	"% 8.3f",
	"%8d",
	"% 8.3f",
	"%8.1f",
};

	///**
	//Output entire tree with all information (see implementation code for details about output format)
	//*/
	//void Player_AI_RL::Output_UCT_Tree()
	//{
	//	gmp->Print("\n========== BEGIN OUTPUT_UCT_TREE ==========\n\nTREE SIZE: %d nodes, memory: %d B (%.3f MB)\n\n", UCTtree_num_nodes, UCTtree_memorySize, UCTtree_memorySize / 1024.0 / 1024.0);
	//	gmp->Print("Leafs < Root\n");
	//	Output_UCT_Tree_Branch(UCTroot);
	//	gmp->Print("\n========== END OUTPUT_UCT_TREE ==========\n\n");
	//}

	//void Player_AI_RL::Output_UCT_Tree_Node_Children(UCTnode* parent)
	//{
	//	printf("\n========== BEGIN OUTPUT_UCT_TREE_NODE_CHILDREN ==========\naction: visits rewards  \tvalue: \tQval\n");
	//	for (int i = 0; i < UCTroot->number_allowed_actions; i++){
	//		if (UCTroot->children[i] != NULL){
	//			printf("   %3d:  %5.0f  %6.1f  \t%3.3f \t %3.3f\n",
	//				UCTroot->children[i]->action_index,
	//				UCTroot->children[i]->visits,
	//				UCTroot->children[i]->rewards,
	//				UCTroot->children[i]->value,
	//				UCTroot->children[i]->Q_value + 0.5
	//				);
	//		}
	//		else{
	//			printf("Untried action: parent->children[%d]\n", i);
	//		}
	//	}
	//	gmp->Print("\n========== END OUTPUT_UCT_TREE_NODE_CHILDREN ==========\n\n");
	//}

	///**
	//Output part of tree starting from branchRoot
	//*/
	//void Player_AI_RL::Output_UCT_Tree_Branch(UCTnode* branchRoot)
	//{
	//	UCTnode* tmpNode;

	//	//print current node and its parents
	//	gmp->Print("%d", branchRoot->action_index);
	//	tmpNode = branchRoot->parent;
	//	while (tmpNode != NULL){
	//		gmp->Print(" < %d", tmpNode->action_index);
	//		tmpNode = tmpNode->parent;
	//	}

	//	//print current nodes' values
	//	gmp->Print("\t :\t %2.1f %2.1f", branchRoot->visits, branchRoot->rewards);

	//	//search deeper in the tree if branchRoot is not a leaf - if has children
	//	if (branchRoot->children != NULL){

	//		//print children info
	//		gmp->Print("\t %d/%d :", branchRoot->number_explored_children, branchRoot->number_allowed_actions);

	//		//print current nodes' children list
	//		for (int i = 0, c = 0; i < branchRoot->number_allowed_actions, c < branchRoot->number_explored_children; i++){
	//			if (branchRoot->children[i] != NULL){
	//				gmp->Print(" %d", branchRoot->children[i]->action_index);
	//				c++;
	//			}
	//		}

	//		gmp->Print("\n");

	//		//recursively call children nodes' output
	//		for (int i = 0, c = 0; i < branchRoot->number_allowed_actions, c < branchRoot->number_explored_children; i++){
	//			if (branchRoot->children[i] != NULL){
	//				Output_UCT_Tree_Branch(branchRoot->children[i]);
	//				c++;
	//			}
	//		}

	//	}
	//	else{
	//		gmp->Print("\n");
	//	}

	//}

	//void Player_AI_RL::Debug_UCT_Tree_MemoryState()
	//{

	//	int size1, size2;

	//	printf("\nTREE MEMORY STATE\n");
	//	printf("Current tree: ");
	//	size1 = Debug_UCT_Tree_Size(UCTroot);
	//	printf("\n");
	//	printf("Memory tree:  ");
	//	size2 = -1;
	//	printf("\n");
	//	printf("Tree info: num nodes: %d size %d\n", UCTtree_num_nodes, UCTtree_memorySize);
	//	printf("Size: current: %d memory: %d\n\n", size1, size2);
	//}

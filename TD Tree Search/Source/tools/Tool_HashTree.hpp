#ifndef _TOM_TOOL_HASHTREE_
#define _TOM_TOOL_HASHTREE_

//#includes
#include <string>
#include <cstdio>
#include "..\tools\Support_MultiPrint.hpp"

//external global variables
extern MultiPrinter * gmp;	//multiprinter object defined in main.hpp

//memory tree structure class definition
#pragma once
class HashTree
{

public:

	enum NODE_COLORTAGS{
		NODE_COLORTAG_INITIAL,
		NODE_COLORTAG_PENDINGDELETE
	};

	//data structure for the search tree
	static class StateActionRecord {

	public:

		// identification
		int actionID;			//action unique identificator (may not be used)

		// learning values
		double Q_value;					//current state (or state-action) value
		double offline_delta_Q;			//pending update of Q-value (used for offline updating)
		int Z_traceTag;					//flag for eligibility traces

		// memorized observations and calculations	
		double num_visited_total;		//visit counter in total (even multiple visits per episode)
		double num_visited_episodes;	//visit counter	that updates once by episode, is equal to "num_visited_total" if transpositions are not used
		double last_estimated_value;	//last estimated value by the control policy (and by considering opponent's model - may be minimizing or maximizing the reward)
		double maxObservedReturn;		//highest observed return for this state
		double minObservedReturn;		// lowest observed return for this state
		double maxBranchQval;			//highest Q-value in this node's branch
		double minBranchQval;			// lowest Q-value in this node's branch
		double maxChildQval;			//highest Q-value among this node's children
		double minChildQval;			// lowest Q-value among this node's children

		// memorize creation time (usually equals to first visit)
		int created_mainGameStep;
		int created_episode;		//global episode number (not in current batch of episodes for the last external move)
		int created_simulatedGameStep;

		// memorize visit time
		int last_visit_mainGameStep;
		int last_visit_episode;		//global episode number (not in current batch of episodes for the last external move)
		int last_visit_simulatedGameStep;

		// memorized policy
		int onPolicy_selected_child_index;	//remember which child was selected by the exploratory policy
		double offPolicy_selected_child_value;	//remember the value of the off-policy would-be-selected child
												//(for Q-learning this is the node with highest value, by ignoring the exploratory bias)
	};

	//tree node
	static class TreeNode
	{

	public: 

		TreeNode();

		//tree structure variables
		int num_children;
		TreeNode* parent;
		TreeNode** children;
		int* childrenActions;

		//index in parent's children array
		int in_parent_seq_index;

		//pointer to data record
		StateActionRecord* data;
		int hashKey;			//index in hash table (unique identificator, may not be used)

		//color tag for performing recursive graph-based operations (e.g., delete a graph)
		int colorTag;
	};

	HashTree(double maxTreeSizeGB, int sizeHashMap = 0);
	virtual ~HashTree();

	virtual void Init(double maxTreeSizeGB, int sizeHashMap);
	virtual void Allocate_Memory();
	virtual void Clear_Memory();
	virtual void Reset();

	virtual TreeNode* Get_State_ActionID(TreeNode* state, int actionID);
	virtual TreeNode* Find_Child_ActionID(TreeNode* node, int actionID);
	virtual TreeNode* Crop_Tree_ActionID(int actionID);	//starts from the root, releases memory, changes the root
	virtual void Delete_Branch(TreeNode* node);
	virtual void Delete_Single_TreeNode(TreeNode* node);
	virtual void Delete_Single_HashNode(TreeNode* node);

	virtual void Output_HashTable(char* printLinePrefix = NULL);
	virtual void Output_Tree(char* printLinePrefix = NULL, int compare_episode = -1, int output_depth = -1);
	virtual void Output_TreeBranch(TreeNode* node, int depth = 0, char* printLinePrefix = NULL, int compare_episode = -1, int output_depth = -1);
	virtual void Output_SingleNode_LineStats(TreeNode* node);
	//virtual stateActionRecord* Find_Node_ActionID(int actionID);

	//statics
	static const std::string class_name;
	static const char * const TreeNodeAtrLabels[];
	static const char * const TreeNodeAtrFormat[];
	static const char * const StateActionAtrLabels[];
	static const char * const StateActionAtrFormat[];

	//configuration
	double treeMaxMemorySize;			//maximum size of tree in memory
	int  hashMapSize;

	//memory structures
	TreeNode** hashMap;
	TreeNode* root;

	//current state
	bool	is_initialized;
	bool	is_allocated;
	int		numAllocNodes;		//number of allocated hash/tree nodes
	double	allocMemorySize;	//size of all allocated nodes (in Bytes)
	bool	memory_exceeded;
	int		treeDepth;


	////public procedures - debug and visualization	
	//virtual void Output_UCT_Tree();
	//virtual void Output_UCT_Tree_Branch(UCTnode*);
	//virtual void Output_UCT_Tree_Node_Children(UCTnode*);
	//virtual void Debug_UCT_Tree_MemoryState();
	//virtual int  Debug_UCT_Tree_Size(UCTnode*);




	//
	//virtual void		UCT_Tree_Trim(UCTnode* branchRoot, int remaining_depth);
	//virtual void		UCT_Tree_Delete(UCTnode* branchRoot);
	//virtual void		UCT_Tree_Reset();

	//virtual UCTnode*	UCT_Tree_Node_Init(int action_seq_index, int child_seq_index, UCTnode* parent);	//node: initialize
	//virtual void		UCT_Tree_Node_AllocateList(UCTnode* node);	//node: allocate children list
	//virtual void		UCT_Tree_Node_Reset(UCTnode* node);		//node: reset values to initial

};

#endif
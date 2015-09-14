#ifndef _TOM_PLAYER_ENGINE_
#define _TOM_PLAYER_ENGINE_

//#includes
#include "..\core\Game_Interface.hpp"

//defines


//forward declarations
class Game_Engine;

//class definition
#pragma once
class Player_Engine
{

public:

	//enums
	static const struct THRESHOLD_FUNCTIONS {
		enum TYPE {
			SIGMOID_CENTER_ZERO,
			SIGMOID,
			STEP,
			LINEAR,
			ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
		};
	};

	//global constants
	static const int TOMPLAYER_PLAYER_NUMBER = 0;
	static const int  TOMPLAYER_EXTERNAL_RESET_ENABLED = 1;
	static const int  TOMPLAYER_FINAL_OUTPUT_ENABLED = 0;
	static const int  TOMPLAYER_VISUALIZATION_DEPTH = 0;

	//constructor and destructor
	Player_Engine(Game_Engine* = NULL, int = TOMPLAYER_PLAYER_NUMBER);
	virtual ~Player_Engine(){};

	//virtual public procedures
	virtual void Apply_Settings();
	virtual void Reset()			{};
	virtual void New_Game()			{};
	virtual int  Get_Move()			= 0;
	virtual void Before_Move(int)	{};
	virtual void After_Move(int)	{};
	virtual void End_Game()			{};

	//support procedures
	virtual double Neural_Network_Threshold_Function(double input_weight_sum, THRESHOLD_FUNCTIONS::TYPE function_type);

	//virtual public procedures - debug and visualization
	virtual void Output()	{};
	virtual void Output_Settings()	{};

	//public procedures
	void Reset_Settings(Game_Engine* = NULL);

	//public variables - player settings
	Game_Engine* game;
	int player_number;
	bool external_reset_enabled;

	//public variables - player definition
	string player_name;

	//public variables - debug and visualization
	bool final_output_enabled;
	int visualization_depth;

protected:

	//virtual protected procedures
	virtual void Init_Settings()	{};
	virtual void Allocate_Memory()	{};
	virtual void Clear_Memory()		{};

	//protected procedures
	void Initialize();

	//protected variables - object state
	bool is_initialized;
	bool is_allocated;

};

class Player_Human : public Player_Engine
{

public:

	//public procedures
	Player_Human(Game_Engine* game);
	int Get_Move();

};

class Player_Random : public Player_Engine
{

public:

	//public procedures
	Player_Random(Game_Engine* game);
	int Get_Move();

};

class Player_Passive : public Player_Engine
{

public:

	//public procedures
	Player_Passive(Game_Engine* game);
	int Get_Move();

};

class Player_SameMove : public Player_Engine
{

public:

	//public procedures
	Player_SameMove(Game_Engine* game);
	int Get_Move();

	//public variables
	int move;

};

#include "Game_Engine.hpp"

#endif
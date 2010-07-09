/***************************************
* ship_ai.h
* 
* Header file for ship AI
***************************************/

// Timers
#define AIT_WAIT	0
#define MAXAITIMER	1

// AI Types
#define AI_LINE 	0
#define AI_STOP		1
#define AI_PATH		2

// AI Modes
#define AIM_COMBAT	0
#define AIM_SEEK	1
#define AIM_FOLLOW	2
#define AIM_WAIT	3
#define AIM_AUTOPILOT	4
#define AIM_RAMMING	5

// AI Bits
#define AIB_ENABLED	BIT_1
#define AIB_AUTOPILOT	BIT_2
#define AIB_BATTLER	BIT_3
#define AIB_HUNTER	BIT_4
#define AIB_MOB		BIT_5
#define AIB_RAMMER	BIT_6
#define AIB_DRONE	BIT_7

struct shipai_data
{
  P_ship ship, target;
  int flags, type, timer[MAXAITIMER], t_room, mode;
  struct shipgroup_data *group;
  struct shipai_data *next;
};

struct shipgroup_data
{
  struct shipai_data *leader;
  struct shipai_data *ai;
  struct shipgroup_data *next;
};

#define NPC_AI_IDLING   0
#define NPC_AI_ENGAGING 1
#define NPC_AI_CRUISING 2
#define NPC_AI_RUNNING  3
#define NPC_AI_LOOTING  4


struct NPCShipAI
{
    P_ship ship;
    P_char debug_char;
    int mode;
    bool advanced;
    
    
    NPCShipAI(P_ship s, P_char ch = 0);
    void activity();
    void reload_and_repair();

    // General combat
    int t_bearing;
    int t_arc;
    int s_bearing;
    int s_arc;
    float t_range;
    int t_x, t_y;
    int contacts_count;
    bool did_board;
    bool is_heavy_ship;
    bool is_multi_target;
    bool out_of_ammo;
    int new_heading;
    int speed_restriction;

    bool find_current_target();
    bool find_new_target();
    void update_target(int i);
    bool is_valid_target(P_ship t);
    void run_away();
    bool chase();
    int calc_intercept_heading(int h1, int h2);
    bool go_around_land();
    bool check_ammo();
    void set_new_dir();
    bool worth_ramming();
    bool check_ram();
    void ram_target();
    bool charge_target(bool for_boarding);
    bool check_boarding_conditions();
    void board_target();
    void immobile_maneuver();



    // Basic combat
    int active_arc[4]; 
    int too_close;
    bool too_far;

    void basic_combat_maneuver();
    void b_attack();
    bool b_circle_around_arc(int arc);
    bool b_turn_active_weapon();
    bool b_turn_reloading_weapon();
    bool b_make_distance(float distance);
    void b_check_weapons();
    void b_set_arc_priority(int current_bearing, int current_arc, int* arc_priority);





    // Advanced combat
    float prev_hd;
    float curr_x, curr_y;
    int curr_angle[4];
    
    float proj_x, proj_y;
    int proj_angle[4];
    float proj_range;
    int proj_sb;
    int proj_tb;

    float hd_change;

    void predict_target(int steps);

    struct SideProperties
    {
        int ready_timer;
        float damage_ready;
        float max_range;
        float good_range;
        float min_range;
    } side_props[4];
    float min_range_total;

    struct TargetSideProperties
    {
        int ready_timer;
        float damage_ready;
        float max_range;
        float min_range;
        float land_dist;
    } tside_props[4];
    float t_min_range;
    float t_max_range;

    int target_side;
    bool within_target_side;
    int cw_cw, cw_ccw, ccw_cw, ccw_ccw;

    int chosen_side;
    int chosen_rot;

    void advanced_combat_maneuver();
    void a_attack();
    void a_update_side_props();
    void a_update_target_side_props();
    void a_choose_target_side();
    void a_calc_rotations();
    void a_choose_rotation();
    bool a_immediate_turn();
    void a_choose_dest_point();
    void a_apply_chosen_destination();
    void a_predict_target(int steps);



    // Utils
    int check_dir_for_land_from(float x, float y, int heading, float range);
    int get_arc_main_bearing(int arc);
    int get_arc_width(int arc);
    int get_room_in_direction_from(float x, float y, int dir, float range);
    int get_room_at(float x, float y);
    bool get_coord_in_direction_from(float x, float y, int dir, float range, float& rx, float& ry);
    float calc_land_dist(float x, float y, float dir, float max_range);
    static void normalize_direction(int &dir);
    static bool inside_map(float x, float y);
    void send_message_to_debug_char(char *fmt, ... );
};

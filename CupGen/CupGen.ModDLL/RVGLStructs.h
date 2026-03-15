#pragma once
#include <cstdint>

// ============================================================================
// ENUMS
// ============================================================================

enum class GameMode : int32_t {
    NormalRace = 0x01,
    LobbyCustom = 0x02,
    TimeTrial = 0x03,
    OnlineSyncWait = 0x04,
    Replay = 0x05,
    OnlineSyncWait2 = 0x06,
    Exit = 0x07,
    Practice1 = 0x08,
    Practice2 = 0x09,
    TimedRace = 0x0B,
    RaceAlt = 0x0D,
    Tournament = 0x0F,
    FreeRace = 0x10
};

enum class RvglSdlEvent : uint32_t {
    Quit = 0x100,
    MouseButtonDown = 0x200,
    KeyDown = 0x300,
    TextInput = 0x303,
    WindowEvent = 0x403,
    Custom605 = 0x605,
    Custom606 = 0x606,
    Custom607 = 0x607,
    FingerDown = 0x700,
    FingerUp = 0x701,
    FingerMotion = 0x702
};

enum class AiState : int32_t {
    NormalRacing = 0,
    StartupReset = 1,
    TransitionAvoid = 2,
    Avoidance = 3,
    RubberBand = 4,
    Braking = 6,
    PartialAvoidance = 7,
    LeftTrackAltLow = 8,
    LeftTrackAltHigh = 9,
    LeftRecoveryLow = 10,
    LeftRecoveryHigh = 11,
    RightRecoveryLow = 12,
    RightRecoveryHigh = 13
};

enum class AiNodeType : uint8_t {
    Normal = 0x01,
    Shortcut = 0x02,
    Hazard = 0x03,
    HazardAlt = 0x05,
    TurboBoost = 0x09,
    LeadCarTarget = 0x0A,
    FollowCarTarget = 0x0B,
    DeadEnd = 0x0C,
    ShortcutVariant = 0x0F
};

enum class RaceState : int32_t {
    PreInit = 0,
    FadeIn = 1,
    FadeOut = 3,
    EndDetected = 4,
    PausedDisplayed = 5,
    PostRaceCleanup = 6
};

// ============================================================================
// MEMORY-MAPPED STRUCTS
// Disable compiler padding to strictly match RVGL memory offsets.
// ============================================================================
#pragma pack(push, 1)

// ─── Graphics & Context ───

struct RealGLContext {
    uint8_t  header[136];             // +0x0000
    int8_t   debugFlag;               // +0x0088 (0=normal, 1=debug)
    uint8_t  pad_89[7];               // +0x0089
    void* currentFunctionName;     // +0x0090
    void* drawCallParameters;      // +0x0098
    uint8_t  pad_A0[14673];           // +0x00A0
    uint8_t  contextLostFlag;         // +0x39F1 (0=OK, 1=GPU reset/lost)
};

struct GLContextHandle {
    void* vtable;           // +0x00
    void* reserved;         // +0x08
    uint64_t       versionFlags;     // +0x10
    RealGLContext* realContext;      // +0x18
};

struct Vertex {
    float    x, y, z, w;             // +0x00
    uint8_t  r, g, b, a;             // +0x10
    float    u, v;                   // +0x14
    float    pad[4];                 // +0x1C (Extended to 4 to match 0x2C / 44 bytes size)
};

// ─── Cars & Physics ───

struct CarInfo {
    char     internalName[20];       // +0x00
    char     displayName[19];        // +0x14
    char     pad1[29];               // +0x27
    char     tpageFilename[64];      // +0x54
    char     tpageNull;              // +0x93
    char     tcarboxFilename[64];    // +0x94
    char     tcarboxNull;            // +0xD3
    uint8_t  unknown1[16];           // +0xD4
    uint8_t  bestTimeEnabled;        // +0xE4
    uint8_t  selectableByPlayer;     // +0xE5
    uint8_t  selectableByCPU;        // +0xE6
    uint8_t  statisticsEnabled;      // +0xE7
    int32_t  carClass;               // +0xE8
    int32_t  starRating;             // +0xEC
    int32_t  obtainCondition;        // +0xF0
    int32_t  topSpeedStat;           // +0xF4
    int32_t  accelerationStat;       // +0xF8
    int32_t  weightValue;            // +0xFC
    int32_t  transmissionType;       // +0x100
    uint8_t  unknown2[4];            // +0x104
    uint16_t statusFlags;            // +0x108
    uint8_t  isInvalid;              // +0x109
    uint8_t  pad2[6];                // +0x10A
}; // Size: 0x110 (272 bytes)

struct CarEntity {
    int32_t  car_array_index;         // +0x00
    int32_t  car_type;                // +0x04
    void* prev_car;                // +0x08
    void* next_car;                // +0x10
    int32_t  subtype;                 // +0x18
    uint8_t  pad_1C[24];              // +0x1C
    int8_t   ai_steering;             // +0x34
    uint8_t  pad_35[1];               // +0x35
    int8_t   ai_throttle;             // +0x36
    uint8_t  pad_37[1];               // +0x37
    uint16_t control_flags;           // +0x38
    uint8_t  pad_3A[6];               // +0x3A
    void* physics_body_ptr;        // +0x40
    int32_t  car_slot_index;          // +0x48
    uint8_t  pad_4C[124];             // +0x4C
    void* physics_data_ptr;        // +0xC8
    uint8_t  pad_D0[1132];            // +0xD0
    float    current_speed;           // +0x53C
    uint8_t  pad_540[2640];           // +0x540
    float    race_time_accumulator;   // +0xF90
    uint8_t  pad_F94[124];            // +0xF94
    int32_t  lap_count;               // +0x1010
    uint8_t  pad_1014[56];            // +0x1014
    int32_t  cooldown_timer;          // +0x104C
    uint8_t  pad_1050[22404];         // +0x1050
    int32_t  current_zone_section;    // +0x67D4
    uint8_t  pad_67D8[240];           // +0x67D8
    AiState  ai_state_current;        // +0x68C8
    AiState  ai_state_previous;       // +0x68CC
    float    ai_state_timer;          // +0x68D0
    uint8_t  pad_68D4[56];            // +0x68D4
    uint8_t  facing_route;            // +0x690C
    uint8_t  pad_690D[3];             // +0x690D
    int32_t  route_section_index;     // +0x6910
    float    track_t;                 // +0x6914
    float    norm_track_t;            // +0x6918
    uint8_t  pad_691C[4];             // +0x691C
    float    steering_angle;          // +0x6920
    uint8_t  pad_6924[68];            // +0x6924
    float    lookahead_distance;      // +0x6968
    float    max_steer_limit;         // +0x696C
    uint8_t  pad_6970[28];            // +0x6970
    float    speed_cm_s;              // +0x698C
    uint8_t  pad_6990[48];            // +0x6990
    int32_t  race_position;           // +0x69C0
    uint8_t  pad_69C4[12];            // +0x69C4
    uint8_t  reverse_state;           // +0x69D0
    uint8_t  pad_69D1[7];             // +0x69D1
    float    engine_power_current;    // +0x69D8
    float    engine_power_target;     // +0x69DC
    uint8_t  pad_69E0[100];           // +0x69E0
    uint8_t  invincible_flag;         // +0x6A44
    uint8_t  pad_6A45[3];             // +0x6A45
    int32_t  finish_time_ms;          // +0x6A48
    int32_t  final_race_position;     // +0x6A4C
    uint8_t  pad_6A50[52];            // +0x6A50
    int32_t  network_player_id;       // +0x6A84
};

struct PhysicsBody {
    uint8_t  pad_00[36];              // +0x00
    float    pos_x;                   // +0x24
    float    pos_y;                   // +0x28
    float    pos_z;                   // +0x2C
    uint8_t  pad_30[76];              // +0x30
    float    forward_x;               // +0x7C
    float    forward_y;               // +0x80
    float    forward_z;               // +0x84
    uint8_t  pad_88[392];             // +0x88
    int32_t  on_ground_flag;          // +0x210
    int32_t  wheel_contact_count;     // +0x214
    uint8_t  pad_218[48];             // +0x218
    float    collision_normals[7];    // +0x248
    uint8_t  pad_264[60];             // +0x264
    void* owner_car_entity;        // +0x2A0
    uint8_t  pad_2A8[152];            // +0x2A8
    void* behavior_fn_ptr;         // +0x340
    uint8_t  pad_348[272];            // +0x348
    void* saved_behavior[3];       // +0x458
};

// ─── Tracks & Navigation ───

struct TrackInfo {
    char     folderName[16];         // +0x00
    char     displayName[64];        // +0x10
    uint8_t  unknown2[20];           // +0x50
    int32_t  difficultyRating;       // +0x64
    int32_t  gameType;               // +0x68
    int32_t  challengeTime;          // +0x6C
    int32_t  challengeReverseTime;   // +0x70
    uint8_t  unknown3[4];            // +0x74
}; // Size: 0x78 (120 bytes)

struct AINode {
    AiNodeType type;                 // +0x00
    AiNodeType type2;                // +0x01
    uint8_t    pad_02[2];            // +0x02
    float      track_t;              // +0x04
    uint8_t    pad_08[16];           // +0x08
    void* back_link1;           // +0x18
    void* back_link2;           // +0x20
    void* fwd_link1;            // +0x28
    void* fwd_link2;            // +0x30
    float      left_edge[3];         // +0x38
    uint8_t    pad_44[4];            // +0x44
    float      right_edge[3];        // +0x48
    uint8_t    pad_54[12];           // +0x54
    float      center[3];            // +0x60
    uint8_t    pad_6C[60];           // +0x6C
    float      segment_length;       // +0xA8
    uint8_t    pad_AC[10];           // +0xAC
    uint8_t    obstacle_flags;       // +0xB6
};

struct RouteSection {
    float    x, y, z;                // +0x00
    float    route_val;              // +0x0C
    float* fwd_neighbors[4];       // +0x10
    float* bwd_neighbors[4];       // +0x30
};

// ─── Session & Entities ───

struct RaceCarEntry {
    int32_t  car_type;               // +0x00
    int32_t  spawn_type;             // +0x04
    int32_t  car_model;              // +0x08
    int32_t  spawn_quat;             // +0x0C
    uint8_t  pad_10[8];              // +0x10
    int32_t  network_id;             // +0x18
    int32_t  is_local;               // +0x1C
    uint8_t  pad_20[32];             // +0x20
    char     name[16];               // +0x40
}; // Size: 0x50

struct GhostFrame {
    uint32_t timestamp_ms;           // +0x00
    uint8_t  speed_enc;              // +0x04
    uint8_t  pad_05[3];              // +0x05
    float    quat_x;                 // +0x08
    float    quat_y;                 // +0x0C
    float    quat_z;                 // +0x10
    float    quat_w;                 // +0x14
}; // Size: 0x18

#pragma pack(pop)
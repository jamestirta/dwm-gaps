/* See LICENSE file for copyright and license details. */

/* constants */
#define VEDITOR "dav"
#define BROWSER "chromium"
#define TORRENT "qbittorrent" 
#define SCREENSHOT "screenshotnow"
#define DISCORD "discord"

// include colors
#include "/home/james/.local/share/theme/colors.h"

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 17, .gappx = 17};
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;       /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"monospace:size=10","NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[]       = "monospace:size=10";
/* static const char col_gray1[]       = "#222222"; */
/* static const char col_gray2[]       = "#444444"; */
/* static const char col_gray3[]       = "#bbbbbb"; */
/* static const char col_gray4[]       = "#eeeeee"; */
/* static const char col_cyan[]        = "#005577"; */

// non-border
/* static char normbordercolor[]       = "#444444"; */
/* static char normbordercolor[]       = "#2f2f2f"; */
/* static char normbordercolor[]       = "#222222"; */
/* static char normbordercolor[]       = "#000000"; */

// normal text
/* static char normfgcolor[]           = "#bbbbbb"; */
/* static char normfgcolor[]           = "#d3d3d3"; */
/* static char normfgcolor[]           = "#ccc0b2"; */
/* static char normfgcolor[]           = "#dad2c8"; */

// normal border
/* static char normbgcolor[]           = "#222222"; */

// selected window 
/* static char selbordercolor[]        = "#988165"; */
/* static char selbordercolor[]        = "#00ffff"; */
/* static char selbordercolor[]        = "#ffffff"; */
/* static char selbordercolor[]        = "#5cf9cf"; */
/* static char selbordercolor[]        = "#iff0000" */

// top border 
/* static char selbgcolor[]            = "#846e54"; */
/* static char selbgcolor[]            = "#988165"; // same as selected window */
/* static char selbgcolor[]            = "#004763"; */
/* static char selbgcolor[]            = "#7a623c"; */

// border text 
/* static char selfgcolor[]            = "#222222"; */ 
/* static char selfgcolor[]            = "#eeeeee"; */
/* static char selfgcolor[]            = "#ffffff"; */
/* static char selfgcolor[]            = "#d3d3d3"; */
/* static char selfgcolor[]            = "#8d755a"; */

static const char *colors[][3]      = {
      /*               fg         bg         border   */
      [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
      [SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor  },
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
         *WM_CLASS(STRING) = instance, class
           *WM_NAME(STRING) = title
             */
    /* classinstance title  tags maskisfloatingisterminalnoswallow  monitor */
    { "st-256color",              NULL,   NULL,   0,        0,1,0,-1 },
    { NULL,                       "lf",   NULL,   0,        0,1,0,-1 },
    { NULL,                       NULL,   "lf",   0,        0,1,0,-1 },
    { "lf",                       NULL,   NULL,   0,        0,1,0,-1 },
    { "qBittorrent",              NULL,   NULL,   1 << 8,   0,0,0,-1 },
    { "resolve",                  NULL,   NULL,   1 << 1,   0,0,0,-1 },
    { "discord",                  NULL,   NULL,   1 << 1,   0,0,0,-1 },
    { "Audacity",                 NULL,   NULL,   1 << 1,   0,0,0,-1 },
    { "audacity",                 NULL,   NULL,   1 << 1,   0,0,0,-1 },
    { "kdenlive",                 NULL,   NULL,   1 << 1,   0,0,0,-1 },
    { "Gwe",                      NULL,   NULL,   1 << 7,   0,0,0,-1 },
    { "Nvidia-settings",          NULL,   NULL,   1 << 6,   0,0,0,-1 },
    { "nvidia-settings",          NULL,   NULL,   1 << 6,   0,0,0,-1 },
    { "Microsoft Teams - Preview",NULL,   NULL,   1 << 7,   0,0,0,-1 },
    { "jamesdsp",                 NULL,   NULL,   1 << 7,   0,0,0,-1 },
    { "teams-for-linux",          NULL,   NULL,   1 << 7,   0,0,0,-1 },
    { "obs",                      NULL,   NULL,   1 << 8,   0,0,0,-1 },
};
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALT,                          KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/* #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } } */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/dash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
/* static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbordercolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", normfgcolor, NULL }; */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", selfgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
  /* { MODKEY,                       XK_p,      spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } }, */
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  /* { MODKEY,                       XK_f,      togglebar,      {0} }, */
  { MODKEY,                       XK_b,      togglebar,      {0} },
  /* { MODKEY,                    XK_equal,  togglebar,      {0} }, */
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_f,      togglefullscr,  {0}},
  /* { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } }, */
  /* { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } }, */
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_space,  zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY,                       XK_space,  setlayout,      {.v = &layouts[0]} },
  /* { MODK                       XK_f,      setlayout,      {.v = &layouts[1]} }, */
  /* { MODKEY,                    XK_equal,  setlayout,      {.v = &layouts[2]} }, */
  /* { MODKEY,                    XK_space,  setlayout,      {0} }, */
  /* { MODKEY|ShiftM,             XK_space,  togglefloating, {0} }, */
  /* { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, */
  /* { ALT,                           XK_0,      tag,            {.ui = ~0 } }, */
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { ALT,                          XK_comma,  tagmon,         {.i = -1 } },
  { ALT,                          XK_period, tagmon,         {.i = +1 } },
  /* { ALT,                       XK_equal,  quit,            {0} }, */ 
  { MODKEY,                       XK_w,      spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
  { MODKEY,                       XK_m,    spawn,           {.v = (const char*[]){ "dmenusite" , NULL } } },
  { ALT,                          XK_l,    spawn,           {.v = (const char*[]){ "dmenucopy" , NULL } } },
  /* { MODKEY,              XK_d,    spawn,       {.v = (const char*[]){ VEDITOR, NULL } } }, */
  { MODKEY,                       XK_t,      spawn,          {.v = (const char*[]){ TORRENT, NULL } } },
  /* { ALT,                           XK_s,       spawn,       {.v = (const char*[]){ SCREENSHOT, NULL } } }, */
  { MODKEY,                       XK_d,      spawn,          {.v = (const char*[]){ DISCORD, NULL } } },
  /* { ALT,                          XK_p,      spawn,          {.v = (const char*[]){ "st -e paru -Syu --skipreview --needed", NULL } } }, */
  { ALT,                          XK_p,      spawn,          SHCMD("st -e paru -Syu --skipreview --needed")},
  { MODKEY,                       XK_minus,  spawn,          SHCMD("pamixer -d 1")},
  { ALT,                          XK_minus,  spawn,          SHCMD("pamixer -d 3")},
  { MODKEY,                       XK_equal,  spawn,          SHCMD("pamixer -i 1")},
  { ALT,                          XK_equal,  spawn,          SHCMD("pamixer -i 3")},
  { MODKEY,                       XK_s,      spawn,          SHCMD("~/.local/bin/speaker-or-headphone")},
  { ALT,                          XK_m,      spawn,          SHCMD("pamixer -t")},
  { ALT,                          XK_j,      spawn,          SHCMD("/home/james/.local/bin/alias/schedule")},
  { ALT,                          XK_0,      spawn,          SHCMD("[ -z $( pgrep 'obs' ) ] && ~/.local/bin/setmicvol ; ~/.local/bin/alias/obs-kill-picom || picom -b")},
  { MODKEY,                       XK_a,      spawn,          SHCMD("[ -z $( pgrep 'audacity' ) ] && ~/.local/bin/setmicvol ; ~/.local/bin/alias/auda")},
  { MODKEY,                       XK_r,      spawn,          SHCMD("remaps")},
  { MODKEY,                       XK_v,      spawn,          SHCMD("openvpn")},
  { MODKEY,                       XK_c,      spawn,          SHCMD("~/.local/bin/colpick")},
  { MODKEY,                       XK_s,      spawn,          SHCMD(SCREENSHOT)},
  { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = -5 } },
  { MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = +5 } },
  { MODKEY|ShiftMask,             XK_0,      setgaps,        {.i = GAP_RESET } },
  { MODKEY|ShiftMask,             XK_9,      setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

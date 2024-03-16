/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;        /* vertical padding of bar */
static const int sidepad            = 0;        /* horizontal padding of bar */
static const int overviewgappo      = 24;       /* overview时窗口与边缘的缝隙大小 */
static const int overviewgappi      = 60;       /* overview时窗口与窗口的缝隙大小 */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:style=Regular:size=10:antialias=true:autohint=true",
                                        "WenQuanYi Micro Hei:style=Regular:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "Hack Nerd Font:style=Regular:sirze=10";
static const char col_gray1[]       = "#000000"; /* 状态条底色 */
static const char col_gray2[]       = "#444444"; /* 当static const unsigned int borderpx不为0时，非活动窗口外边框颜色 */
static const char col_gray3[]       = "#eeeeee"; /* 当前非活动的title字体颜色 */
static const char col_gray4[]       = "#ffffff"; /* 当前活动的title字体颜色 */
static const char col_cyan[]        = "#005577"; /* title底色 */
static const unsigned int baralpha = 0x46;       /* 状态栏透明度 */
static const unsigned int borderalpha = OPAQUE;  /* 边框透明度 */
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
    [SchemeUnderline] = { "#7799AA", NULL, NULL }, 
    [SchemeSelTag] = { "#eeeeee", "#333333", NULL },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border     */
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
    [SchemeSelTag] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "󰣇", "", "󰘅", "󰈙", "󰕧", "󰎈", "󰅩", "", "" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


/* overviewlayouts */
static const char *overviewtag = "OVERVIEW";
static const Layout overviewlayout = { "",  overview };

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[G]",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-combi-modi", "window,drun,run,ssh", "-font", "hack 22", "-show", "combi", "-icon-theme", "Papirus","-show-icons", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *fsearchcmd[]  = { "fsearch", "gui", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname, "--class", "floatingTerminal" };
static const char *volumetoggle[] = { "/home/xiaosu/suckless/dwm/scripts/volumetoggle.sh", NULL };
static const char *volumeup[] = { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *volumedown[] = { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *inclight[] = { "light", "-A", "10", NULL };
static const char *declight[] = { "light", "-U", "10", NULL };
static const char *screenshot[] = { "flameshot", "gui", NULL };
static const char *delayedscreenshot[] = { "flameshot", "gui", "-d", "2000", NULL };
static const char *screenlock[] = { "/home/xiaosu/suckless/dwm/scripts/lock.sh", NULL };

#include "movestack.c"
static const Key keys[] = {
    /* modifier                     key        function        argument */
    { 0,                            XF86XK_AudioMute,          spawn,       {.v = volumetoggle} },
    { 0,                            XF86XK_AudioRaiseVolume,   spawn,       {.v = volumeup} },
    { 0,                            XF86XK_AudioLowerVolume,   spawn,       {.v = volumedown} },
    { 0,                            XF86XK_MonBrightnessUp,    spawn,       {.v = inclight} },
    { 0,                            XF86XK_MonBrightnessDown,  spawn,       {.v = declight} },
    { 0,                            XK_Print,  spawn,          {.v = screenshot} },
    { Mod1Mask|ShiftMask,           XK_a,      spawn,          {.v = screenshot} },
    { Mod1Mask|ShiftMask,           XK_d,      spawn,          {.v = delayedscreenshot} },
    { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = screenlock} },
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = fsearchcmd} },
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY,                       XK_q,      toggleoverview, {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
    { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} }, //快速按两次，关闭dwm
    { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, //重启dwm
    { MODKEY,                       XK_o,      winview,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
    { ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
    { ClkStatusText,        MODKEY,         Button1,        sigstatusbar,   {.i = 6} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


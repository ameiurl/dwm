/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2;        /* border pixel of windows */
static const unsigned int gappx    = 5;        /* gaps between windows */
static const unsigned int snap     = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray       = 1;     /* 0 means no systray */
static const int showbar           = 1;        /* 0 means no bar */
static const int topbar            = 0;        /* 0 means bottom bar */
static const char *fonts[]         = { "SauceCodePro Nerd Font Mono:size=22" };
static const char dmenufont[]       = "SauceCodePro Nerd Font Mono:size=22";
// static const char col_gray[]       = "#CCCCCC";
// static const char col_blue[]       = "#3498DB";
// static const char col_blue2[]      = "#0D47A1";
// static const char col_black[]      = "#000000";
// static const char col_white[]      = "#FFFFFF";

static const char col_gray1[]      = "#212121";
static const char col_gray2[]      = "#bbbbbb";
static const char col_gray3[]      = "#424242";
static const char col_black[]      = "#000000";
static const char col_white[]      = "#ffffff";
static const char col_red1[]       = "#ff0000";
static const char col_red2[]       = "#770000";
static const char col_green1[]     = "#00ff00";
static const char col_green2[]     = "#007700";
static const char col_blue1[]      = "#0000ff";
static const char col_blue2[]      = "#000077";
static const char col_yellow1[]    = "#ffff00";
static const char col_yellow2[]    = "#777700";
static const char col_cyan1[]      = "#8be9fd";
static const char col_cyan2[]      = "#036175";


static const unsigned int baralpha 	  = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const Bool viewontag           = True;     /* Switch view on tag switch */
static const char *colors[][3]        = {
	/*              fg             bg           border   */
    [SchemeNorm]  = { col_gray2,   col_gray1,   col_gray3 },
	[SchemeSel]   = { col_white,   col_gray3,   col_gray3 },
	[SchemeHid]   = { col_gray3,   col_gray1,   col_gray3 },
	[SchemeFree]  = { col_green1,  col_green2,  col_gray3 },
	[SchemeUnacc] = { col_red1,    col_red2,    col_gray3 },
	[SchemeAct]   = { col_yellow1, col_yellow2, col_gray3 },
	[SchemeInact] = { col_blue1,   col_blue2,   col_gray3 },
	[SchemeCache] = { col_cyan1,   col_cyan2,   col_gray3 },
};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]   = { OPAQUE, baralpha, borderalpha },
	[SchemeHid]   = { OPAQUE, baralpha, borderalpha },
	[SchemeFree]  = { OPAQUE, baralpha, borderalpha },
	[SchemeUnacc] = { OPAQUE, baralpha, borderalpha },
	[SchemeAct]   = { OPAQUE, baralpha, borderalpha },
	[SchemeInact] = { OPAQUE, baralpha, borderalpha },
	[SchemeCache] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", " ", "", "", "", "", "", "", "" };
// static const char *tags[] = { "󰅩", "", "", "", "", "" , "  ", "  ", "  ", "  ",""};
// static const char *tagsalt[] = { "󰖟", "", "", "󰙯", "", "󰎈", "󰕝", "" };
//static const char *tags[] = { " ", " ", " ", " ", " ", " ", "" };
// static const char *tags[] = { "", "", "", "", "󰈹", "󰘬", "󰠖", "󱍢", "", "", "", ""};
// static const char *tags[] = { "", "", "",  "", "", "","", "", ""};
// static const char *tags[] = {"", "", "", "", "", " ", " ", "  "};
// static const char *tags[] = { "", "", "", "", "", "", "", "", "", "" };
 
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title         tags mask     isfloating   monitor */
	{ "Peek",        NULL,       NULL,         0,            1,           -1 },
	{ "flameshot",   NULL,       NULL,         0,            1,           -1 },
	{ "scrcpy",      NULL,       NULL,         0,            1,           -1 },
	{ "idea",        NULL,       "win0",       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tile",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray2, "-sb", col_cyan2, "-sf", col_white, NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *termcmd[]   = { "st", NULL };
static const char *flameshotcmd[]  = { "flameshot", "gui", NULL };
static const char *edgecmd[]  = { "microsoft-edge-stable", NULL };
static const char *chromecmd[]  = { "google-chrome-stable", NULL };
static const char *ranger[]    = { "st", "-e", "ranger", NULL };
static const char *nvim[]      = { "st", "-e", "nvim", NULL };
static const char *music[]     = { "electron-netease-cloud-music", NULL };
static const char *lightup[] = {"xbacklight", "-inc", "10", NULL};
static const char *lightdown[] = {"xbacklight", "-dec", "5", NULL};
static const char *soundup[] = {"amixer", "-qM", "sset", "Master", "5%+", "unmute", NULL};
static const char *sounddown[] = {"amixer", "-qM", "sset", "Master", "10%-", "unmute", NULL};
static const char *mute[] = {"amixer", "-qM", "sset", "Master", "toggle", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slockcmd } },
	{ MODKEY|ShiftMask,           	XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_a,	   spawn,          {.v = flameshotcmd } },
	{ MODKEY,                       XK_e,	   spawn,          {.v = edgecmd } },
	{ MODKEY,                       XK_c,	   spawn,          {.v = chromecmd } },
	{ MODKEY,						XK_r,	   spawn,          {.v = ranger } },
	{ MODKEY,						XK_n,	   spawn,          {.v = nvim } },
	{ MODKEY|ShiftMask,				XK_e,	   spawn,          {.v = music } },
	{ MODKEY,			            XK_Left,   spawn,	       {.v = lightup } },
	{ MODKEY,			            XK_Right,  spawn,	       {.v = lightdown } },
	{ MODKEY,			            XK_Up,	   spawn,	       {.v = soundup } },
	{ MODKEY,			            XK_Down,   spawn,	       {.v = sounddown } },
	{ MODKEY,			            XK_F8,	   spawn,	       {.v = mute } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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


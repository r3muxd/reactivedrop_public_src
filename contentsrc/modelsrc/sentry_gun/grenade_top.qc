$modelname "sentry_gun/grenade_top.mdl"

$body "base" "sentry_top_base.dmx"
$body "grenade_top" "grenade_top.dmx"

$surfaceprop "weapon"
$contents "solid"

$cdmaterials "swarm/models/SentryGun"

$attachment "muzzle" "ValveBiped.sentrygun_Barrel" 0 0 0 rotate 0 0 90
$attachment "atttach_camera" "ValveBiped.sentrygun_camera_lense2" 0 0 0 rotate 0 0 -90
$attachment "eject1" "ValveBiped.sentrygun_eject1" 0 0 0 rotate 0 0 -90
$attachment "attach_light" "ValveBiped.sentrygun_screen" -2 0 -2 rotate 180 90 0

$poseparameter "aim_yaw" -120 120 loop 360
$poseparameter "aim_pitch" -90 45 loop 360
$poseparameter "ammo_remaining" 1 20

$sequence "bindpose" {
	"sentry_anims/bindpose.dmx"
	activity ACT_OBJ_IDLE 1
}

$animation "camera_aim_right" "sentry_anims/camera_aim.dmx" {
	frame 0 0
	subtract "bindpose" 0
}
$animation "camera_aim_mid" "sentry_anims/camera_aim.dmx" {
	frame 1 1
	subtract "bindpose" 0
}
$animation "camera_aim_left" "sentry_anims/camera_aim.dmx" {
	frame 2 2
	subtract "bindpose" 0
}
$animation "pitch_down" "sentry_anims/sentry_pitch.dmx" {
	frame 0 0
	subtract "bindpose" 0
}
$animation "pitch_mid" "sentry_anims/sentry_pitch.dmx" {
	frame 1 1
	subtract "bindpose" 0
}
$animation "pitch_up" "sentry_anims/sentry_pitch.dmx" {
	frame 2 2
	subtract "bindpose" 0
}
$animation "disassemble" "sentry_anims/grenade_disassemble.dmx" {
	subtract "bindpose" 0
}
$animation "ammo_remaining" "sentry_anims/grenade_ammo_remaining.dmx" {
	subtract "bindpose" 0
}

$sequence "sentry_fire" {
	"sentry_anims/grenade_sentry_fire.dmx"
	activity ACT_OBJ_RUNNING 1
	fadein 0
	fadeout 0
}

$sequence "sentry_build" {
	"sentry_anims/grenade_sentry_build.dmx"
	activity ACT_OBJ_ASSEMBLING 1
}

$sequence "sentry_updown" {
	"pitch_down" "pitch_mid" "pitch_up"
	autoplay
	blend "aim_pitch" -45 45
	blendwidth 3
	delta
	hidden
}

$sequence "sentry_camera" {
	"camera_aim_right" "camera_aim_mid" "camera_aim_left"
	autoplay
	blend "aim_yaw" -120 120
	blendwidth 3
	delta
	hidden
}

$sequence "sentry_disassemble" {
	"disassemble" "pitch_mid"
	autoplay
	blend "aim_pitch" -90 -45
	blendwidth 2
	delta
	hidden
}

$sequence "sentry_ammo_remaining" {
	"ammo_remaining"
	autoplay
	posecycle "ammo_remaining"
	delta
	hidden
}

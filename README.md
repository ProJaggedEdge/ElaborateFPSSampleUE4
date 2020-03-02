# ElaborateFPSSampleUE4

Developed with Unreal Engine 4.24.2\
Some enhancements and tweaks on the Sample FPS Project provided by Unreal Engine\

Available Features:
	
	Ammo and Clip System:
		Clip Size and Ammo fixed on Start
		Auto-reload when Firing w/ an empty clip
		Ammo auto Pickups, with auto-reload
	
	Reload(R Button):
		Sound Effect
		Appropriate Ammo Count and Clip Change
	
	Explosive Shots:
		Projectiles spawn an explosion and cause a radial impulse
	
	Shooting Recoil:
		Heavy Recoil as shots are explosive
	
	Double-Jump:
		Uses Fuel
		Space Bar while jumping for another one
		Sound Effect
	
	Warp to Focused Area(E Button):
		Quick movement to where the Player Camera is facing
	
	Sprint(Left Shift + Forward Movement):
		Doesn't Work on Strafe Movement
		Stops when Stamina runs out or Player starts strafing

	Fully Automatic Shots with Fixed Fire Rate:
		Holding down the Left Mouse Button will cause auto-fire

	Stamina System:
		Animated Bar(Green, Top) on HUD
		Used by Sprinting and Dashing
		Recovers when not using Stamina

	Fuel System:
		Animated Bar(Blue, Bottom) on HUD
		Used by Double-Jump and Warping
		Fuel auto Pickups

	Dash(Left Alt + Movement):
		Allows for Swift Movement when adding Left Alt to movement in any direction

Todo:\
	Sprint Animation\
	Reload Animation\
	Switchable Fire Modes(Fully Automatic, Burst, Buckshot, Single Shot)\
	Lock-On Fire Mode
========================================================================
    Custom Ringtone Worker (CRW) : Project overview
========================================================================

1. Project purpose.
	1.1.	Checks Ringtone0 registry key for changes and opens 
			RingtoneManager Silverlight application.
	1.2.	Protects "get more" ringtone entry from deletion.
	
2. Architecture.
	2.1.	There are two registry callbacks set for
			* HKEY_CURRENT_USER\ControlPanel\Sounds\RingTone0\Sound
			* HKEY_CURRENT_USER\ControlPanel\Sounds\CustomRingtones\CustomRingtone-PlaceHolder.mp3
	2.2.	Once first callback fires, it calls Shell::Tasks::StartSession.
	2.3.	Once second callback fires (usually on key deletion), its entry automatically gets restored.

3. Terms of usage.
	3.1.	You can use this source code in a way you want.
	3.2.	Limitation: you cannot post modified binary in compiled form unless you
			have a permission from author.
	3.3.	Don't hesistate to ask for permission - if your changes are worth it, 
			they will be allowed.
	3.4.	You cannot claim you're the author of this project or any derivative project.
	3.5.	You cannot sell this project.
	
 © ultrashot 2012-2013
 
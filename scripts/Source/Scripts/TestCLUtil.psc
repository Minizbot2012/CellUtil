Scriptname TestCLUtil extends ObjectReference
{ Test script, requires No .esp renewed and an autobinding file to attach the script to the Player }
Import CLUtil
Event OnInit()
    RegisterForCellload(self)
endevent

Event OnCellChange(Cell cl)
    Debug.Notification("Cell change "+cl.GetFormID())
    Debug.Notification("RGEN EDID "+GetRegion(cl))
EndEvent

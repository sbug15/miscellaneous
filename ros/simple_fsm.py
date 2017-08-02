#!/usr/bin/env python

import rospy
from smach import State, StateMachine

from time import sleep

class One(State):
    def __init__(self):
        State.__init__(self, outcomes=["success", "fail"])

    def execute(self, userdata):
        print "one"
        rospy.sleep(1)
        return "fail"

class Two(State):
    def __init__(self):
        State.__init__(self, outcomes=["success", "fail"])

    def execute(self, userdata):
        print "two"
        rospy.sleep(1)
        return "success"

class Three(State):
    def __init__(self):
        State.__init__(self, outcomes=["success", "fail"])

    def execute(self, userdata):
        print "three"
        rospy.sleep(1)
        return "fail"
        
if __name__ == "__main__":
    sm = StateMachine(outcomes=["success", "fail"])
    with sm:
        StateMachine.add("ONE", One(), transitions={"success": "TWO", "fail": "THREE"})
        StateMachine.add("TWO", Two(), transitions={"success": "ONE", "fail": "THREE"})
        StateMachine.add("THREE", Three(), transitions={"success": "ONE", "fail": "TWO"})
        
    sm.execute()
        

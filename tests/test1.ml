open Misc

let new_parent () =
  display "This process is going to be the new parent" ; 
  display "For the moment, I do sleep" ;
  Unix.sleep 1000

let still_parent child_pid new_parent_pid =
  display "I'm going to move ownerchip from me, %d, to one of my child, %d" child_pid new_parent_pid ;
  display "Ok, now I wait" ;
  match Unix.waitpid [] child_pid with
      _, (Unix.WEXITED s)
    | _, (Unix.WSIGNALED s) 
    | _, (Unix.WSTOPPED s) -> display "on main parent, returned with code %d" s  

let parent pid = 
  display "Parent process has launch child with pid %d" pid ; 
  display "Now I start a new baby" ;
  match Unix.fork () with 
      0 -> new_parent () 
    | npid -> still_parent pid npid

let child () = 
  display "Child process launched" ;
  Ptrace.trace_me () ; 
  display "Now I'm ready to be traced" ;
  Unix.sleep 5 ;
  exit (10) 

let _ = 
  display "tracking programs with ptrace, test1" ; 
  match Unix.fork () with 
      0 -> child () 
    | pid -> parent pid 
  
  

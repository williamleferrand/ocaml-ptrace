open Misc

let new_parent () =
  display "This process is going to be the new parent" ; 
  display "For the moment, I do sleep" ;
  Unix.sleep 1000

let still_parent child_pid new_parent_pid =
  display "I'm going to move ownerchip from me, %d, to one of my child, %d" child_pid new_parent_pid ;
  display "Ok, I sleep for a few seconds" ;
  Unix.sleep 1000
  

let parent pid = 
  display "Parent process has launch child with pid %d" pid ; 
  display "Now I start a new baby" ;
  match Unix.fork () with 
      0 -> new_parent () 
    | npid -> still_parent pid npid

let child () = 
  display "Child process launched" ;
  Unix.sleep 1000

let _ = 
  display "tracking programs with ptrace, test1" ; 
  match Unix.fork () with 
      0 -> child () 
    | pid -> parent pid 
  
  

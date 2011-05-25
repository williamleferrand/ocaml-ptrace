let display fmt =  
  Printf.ksprintf (fun s -> print_endline s; flush stdout) fmt 

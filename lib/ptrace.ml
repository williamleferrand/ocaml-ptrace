(* ptrace *)

external ptrace : int -> int -> int -> int -> int = "ocaml_ptrace"

(* user functions *)

external trace_me : unit -> unit = "ocaml_trace_me"
external attach : int -> unit = "ocaml_attach"
external detach : int -> unit = "ocaml_detach"

external cont : int -> int -> unit = "ocaml_cont" 

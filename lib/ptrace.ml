(* ptrace *)

external ptrace : int -> int -> int -> int -> int = "ocaml_ptrace"

(* user functions *)

external trace_me : unit -> unit = "ocaml_trace_me"


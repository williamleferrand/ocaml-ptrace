(* ptrace *)

external ptrace : int -> int -> int -> int -> int = "ocaml_ptrace"

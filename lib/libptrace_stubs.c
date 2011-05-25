#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>


#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/ptrace.h>

value ocaml_ptrace (value ocaml_request, value ocaml_pid, value ocaml_addr, value ocaml_data) {
  CAMLparam4 (ocaml_request, ocaml_pid, ocaml_addr, ocaml_data); 
  
  int rc ; 

  int request = Int_val (ocaml_request) ;
  int pid = Int_val (ocaml_pid) ; 
  caddr_t addr = (caddr_t) (Int_val (ocaml_addr)); 
  int data = Int_val (data) ;
  
  rc = ptrace (request, pid, addr, data); 
  
  CAMLreturn (Val_int (rc)) ;  
}

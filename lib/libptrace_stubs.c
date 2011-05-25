#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>


#include <errno.h>

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


/*
 * trace_me
 */ 

value ocaml_trace_me (value ocaml_unit) {
  CAMLparam1 (ocaml_unit); 
  
  int rc ; 

  rc = ptrace (PT_TRACE_ME, 0, 0, 0); 

  if (rc) caml_failwith ("libptrace: trace_me returned a nonzero code"); 
  
  CAMLreturn (Val_unit); 
}


/*
 * attach
 */

value ocaml_attach (value ocaml_pid) {
  CAMLparam1 (ocaml_pid) ; 

  int rc ; 

  rc = ptrace (PT_ATTACH, Int_val (ocaml_pid), 0, 0) ; 

  if (rc) 
    {
     printf ("errno: %d\n", errno); 
     caml_failwith ("libptrace attach returned non zero code") ; 
    }
  CAMLreturn (Val_unit) ;
}

/*
 * detach
 */

value ocaml_detach (value ocaml_pid) {
   CAMLparam1 (ocaml_pid) ; 

  int rc ; 

  rc = ptrace (PT_DETACH, Int_val (ocaml_pid), 0, 0) ; 

  if (rc) 
    {
     printf ("errno: %d\n", errno); 
     caml_failwith ("libptrace detach returned non zero code") ; 
    }
  CAMLreturn (Val_unit) ;
}


/*
 * cont
 */

value ocaml_cont (value ocaml_pid, value ocaml_signal) {
  CAMLparam2 (ocaml_pid, ocaml_signal); 
  
  caddr_t addr ;
  int sig ;
  int rc ;
  
  addr = (caddr_t) 0; 

  sig = Int_val (ocaml_signal); 
  
  printf ("signal: %d\n", sig) ;

  rc = ptrace (PT_CONTINUE, Int_val (ocaml_pid), addr, sig); 

  if (rc) {
      printf ("errno: %d\n", errno); 
      caml_failwith ("libptrace cont returned non zero code") ;
    }; 

  CAMLreturn (Val_unit) ; 
}


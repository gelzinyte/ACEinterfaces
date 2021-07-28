  
#include <julia.h>
#include <stdio.h>

JULIA_DEFINE_FAST_TLS() // only define this once, in an executable (not in a shared library) if you want fast code.

int main(int argc, char *argv[])
{
    /* required: setup the Julia context */
    jl_init();
    jl_eval_string("using Pkg; Pkg.activate(\".\"); Pkg.instantiate(; verbose=true);");

    /* run Julia commands */
    jl_eval_string("using ACE, JuLIP");

   /* load a potential */ 
    jl_eval_string("D = load_json(\"randpot.json\"); V = read_dict(D)");

   /* create random data defining structure */ 
   double* cell = {5.0, 2.0, 0.0, 2.0, 5.0, 0.0, 0.0, 0.0, 3.0};
   short* bc = {true, false, true};
   double* positions = { 0.0, 0.0, 0.0, 
                        3.0, 0.2, 0.5, 
                        0.1, 2.5, 2.8 };
   int* Z = {28, 28, 8};

   /* create the JuLIP structure */ 
   jl_eval_string("_Z = ");
   jl_eval_string("@show Z");
   // etc
   jl_eval_string("at = Atoms(X = _X, Z = _Z, pbc = _bc, cell = _cell)")

   // /* evaluate the energy on the structure */ 
   // jl_value_t *jl_E = jl_eval_string("energy(V, at)");
   // if jl_typeis(jl_E, jl_float64_type) {
   //    double E = jl_unbox_float64(jl_E);
   //    printf("E = %f \n", E);
   // } else {
   //    printf("Can't identify the return type!!!");
   // }

    /* strongly recommended: notify Julia that the
         program is about to terminate. this allows
         Julia time to cleanup pending write requests
         and run all finalizers
    */
    jl_atexit_hook(0);
    return 0;
}

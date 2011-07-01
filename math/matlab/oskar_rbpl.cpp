#include <mex.h>
#include "math/Random.h"
#include <vector>


// Interface function - can call anything from here...
//
// nlhs = The number of left-hand arguments, or the size of the plhs array.
// plhs = An array of left-hand output arguments.
// nrhs = The number of right-hand arguments, or the size of the prhs array.
// prhs = An array of left-hand output arguments.
void mexFunction(
        int /*num_returns*/,       // out
        mxArray ** return_ptrs,    // out
        int num_args,              // in
        const mxArray ** arg_ptrs  // in
)
{
    // Check for proper number of arguments.
    if (num_args < 6 || num_args > 7)
    {
        mexPrintf("Number of args = %d\n", num_args);
        mexErrMsgTxt("ERROR: Expecting arguments "
                "(n, min, max, threshold, power1, power2, seed)");
    }

//    if (num_returns != 1)
//    {
//        mexPrintf("WARNING: expecting a vector of values to be returned");
//    }

    // Grab inputs
    const int n            = (int)*mxGetPr(arg_ptrs[0]);
    const double min       = (double)*mxGetPr(arg_ptrs[1]);
    const double max       = (double)*mxGetPr(arg_ptrs[2]);
    const double threshold = (double)*mxGetPr(arg_ptrs[3]);
    const double power1    = (double)*mxGetPr(arg_ptrs[4]);
    const double power2    = (double)*mxGetPr(arg_ptrs[5]);
    const int seed = (num_args == 6) ? 1 : (int)*mxGetPr(arg_ptrs[6]);
//    mexPrintf("Inputs: (%d)\n", num_args);
//    mexPrintf("  = n         = %d\n", n);
//    mexPrintf("  = min       = %g\n", min);
//    mexPrintf("  = max       = %g\n", max);
//    mexPrintf("  = threshold = %g\n", threshold);
//    mexPrintf("  = power1    = %f\n", power1);
//    mexPrintf("  = power2    = %f\n", power2);
//    mexPrintf("  = seed      = %d\n", seed);

    // Vector of values to return.
    const int rows = 1;
    const int cols = n;
    return_ptrs[0] = mxCreateNumericMatrix(rows, cols, mxDOUBLE_CLASS, mxREAL);
    double * rand = mxGetPr(return_ptrs[0]);

    rand[0] = Random::broken_power_law<double>(min, max,
            threshold, power1, power2, seed);
    for (int i = 0; i < n; ++i)
    {
        rand[i] = Random::broken_power_law<double>(min, max,
                threshold, power1, power2);
    }
}
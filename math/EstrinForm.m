(*
  Write polynomial P[x] in Estrin's scheme.
  x: variable
  c: list of coefficients, such that
     P[x] = c[[1]] + c[[2]] x + c[[3]] x^2 + ...
 *)
EstrinForm[x_, c_List] :=
    Module[{d, ci, n = Length[c]},
           ci = PadRight[c, n+2];
           d = Table[ci[[2i+1]] + ci[[2i+2]] x, {i, 0, Floor[n/2]}];
           If[n <= 2,
              First[d],
              EstrinForm[x^2, d]
           ]
    ];

(* test *)

On[Assert];

P[x_, c_List] := Sum[c[[k]] x^(k-1), {k, 1, Length[c]}]

For[n = 0, n < 20, n++,
    coeffs = Table[c[i], {i,1,n}];
    Assert[Expand[P[x, coeffs] - EstrinForm[x, coeffs]] == 0];
]

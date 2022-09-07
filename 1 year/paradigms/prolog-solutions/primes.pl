composite(1) :- !.

prime(2) :- !.

prime(N) :- 
	N > 2, 
	\+ composite(N), !.

cross_off(I, N, INC) :- 
	I =< N, assert(composite(I)), 
	I1 is I + INC, 
	cross_off(I1, N, INC), !.
	
cross_off(I, N, INC).

init(MAX_N) :- 
	cross_off(4, MAX_N, 2), 
	go_up(3, MAX_N).

go_up(CUR, MAX_N) :- 
	CUR =< MAX_N, CUR1 is CUR + 2, 
	do_crossing(CUR, MAX_N), 
	go_up(CUR1, MAX_N).

do_crossing(CUR, MAX_N) :- 
	prime(CUR),
	CUR_SQUARE is CUR * CUR, 
	CUR2 is CUR + CUR, 
	cross_off(CUR_SQUARE, MAX_N, CUR2), !.
	
do_crossing(CUR, MAX_N).

list_to_num([], 1, _) :- !.

list_to_num([H | T], N, CUR) :- 
	CUR =< H, 
	list_to_num(T, N1, H), 
	N is N1 * H.

num_to_list(N, D, [N]):-
	D * D > N, !.
num_to_list(N, D, [H | T]):-
	mod(N, D) =:= 0,
	H is D,
	N1 is div(N, D),
	num_to_list(N1, D, T).
    
num_to_list(N, 2, L):-
	mod(N, 2) > 0,
	num_to_list(N, 3, L), !.

num_to_list(N, D, L):-
	mod(N, D) > 0,
	D > 2,
	D1 is D + 2,
	num_to_list(N, D1, L).

prime_divisors(1, []) :- !.

prime_divisors(N, L) :-
	number(N),
	N > 1,
	num_to_list(N, 2, L), !.

prime_divisors(N, L) :-
	list_to_num(L, N, 2).

to_K_sys(0, _, []).

to_K_sys(N, K, [R | T]) :- 
	N > 0, 
	R is mod(N, K), 
	N1 is div(N, K), 
	to_K_sys(N1, K, T), !.

prime_palindrome(N, K) :- 
	prime(N), 
	to_K_sys(N, K, S), 
	reverse(S, S).

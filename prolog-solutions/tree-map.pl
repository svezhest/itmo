merge(node(Y1, K1, V1, L1, R1), node(Y2, K2, V2, L2, R2), node(Y1, K1, V1, L1, Merged)) :-
	Y1 > Y2, merge(R1, node(Y2, K2, V2, L2, R2), Merged), !.
merge(node(Y1, K1, V1, L1, R1), node(Y2, K2, V2, L2, R2), node(Y2, K2, V2, Merged, R2)) :-
	Y1 =< Y2, merge(node(Y1, K1, V1, L1, R1), L2, Merged), !.
merge(Node, nil, Node) :- !.
merge(nil, Node, Node) :- !.

split(nil, _, _, nil, nil) :- !.
split(node(Y, K, V, L, R), Key, r, node(Y, K, V, L, R1), Node2) :-
	K < Key, split(R, Key, r, R1, Node2), !.
split(node(Y, K, V, L, R), Key, r, Node1, node(Y, K, V, L2, R)) :-
	K >= Key, split(L, Key, r, Node1, L2), !.
	split(node(Y, K, V, L, R), Key, l, node(Y, K, V, L, R1), Node2) :-
	K =< Key, split(R, Key, l, R1, Node2), !.
split(node(Y, K, V, L, R), Key, l, Node1, node(Y, K, V, L2, R)) :-
	K > Key, split(L, Key, l, Node1, L2), !.

map_put(TreeMap, Key, Value, Result) :- 
	split(TreeMap, Key, r, SubTree_left, Node_t), split(Node_t, Key, l, _, SubTree_right), rand_int(1000, Y), 
	NewNode = node(Y, Key, Value, nil, nil), merge(SubTree_left, NewNode, Half_res), merge(Half_res, SubTree_right, Result).

map_build([], nil) :- !.
map_build([(Key, Value) | T], TreeMap) :- 
	map_build(T, OldMap), map_put(OldMap, Key, Value, TreeMap).

map_get(node(_, K, V, _, _), K, V) :- !.
map_get(node(_, K, _, _, R), Key, Value) :-
	Key > K, map_get(R, Key, Value), !.
map_get(node(_, K, _, L, _), Key, Value) :-
	Key < K, map_get(L, Key, Value), !.

map_remove(nil, Key, nil) :- !.
map_remove(TreeMap, Key, Result) :- 
	split(TreeMap, Key, r, SubTree_left, Node_t), split(Node_t, Key, l, _, SubTree_right), 
	merge(SubTree_left, SubTree_right, Result).

last(node(_, K, _, _, nil), K) :- !.
last(node(_, _, _, _, R), Key) :- last(R, Key), !.

map_floorKey(Map, Key, FloorKey) :- split(Map, Key, l, Node, _), last(Node, FloorKey).

# C++

Let $$n = $$  number of cities.
Let $$r = $$ `len(roads)`, i.e. number of edges.

## Runtime

O(r + n) best case, O(r + n^2) worst case

* ParseAjacency - O(r)
* CreateCityRanks - O(n)
* GetMaxNetworkRank - O(# of cities with in-degree equal to the highest or second highest in-degree)
    * O(1) best case, when all cities have unique in-degree and the two highest-in-degree cities are not connected.
    * O(n^2) worst case, when all cities have the same in-degree.


## Memory

O(r + n)


### METHODOLOGY ###
For fairness, I tested the following the sorts with a dataset of 1000 random elements, ranging from -1000 to 1000:
- Bubble Sort
- Bubble Sort with Boolean Tweak
- Cocktail-Shaker Sort
- Cocktail with Boolean Tweak
- Insertion Sort
- Selection Sort
- Shell Sort
- Merge Sort

I did the test multiple times.

### FINDINGS ###
- MergeSort performed consistently the best, with O(nlog(n)) consistency across the board
- ShellSort also performed within O(nlog(n)), but always had more comparisons than MergeSort
- Insertion Sort was the best out of the primitive sorts, O(n^2)
- Cocktail Sort with boolean tweak followed, O(n^2)
- Selection Sort may be perferrable on systems where writes/swaps are expensive (never exceeded n-1 swaps)
- Bubble with Boolean Tweak follows, performing O(n^2)
- Without the boolean tweak, Bubble and Cocktail performed always at worst case, since they did not know when they were sorted.

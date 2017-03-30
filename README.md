# homework3
Qiyu Xiao(qx344)


Below is time(second) consumed when transfering single int with three hosts crunchy1,crunchy3 and crunchy4 with option -ppn 1 

| Thread Num/ Loop  | 10 | 50 | 100 | 500 | 
| --- | --- | --- | --- | --- | 
| 10 | 0.060414 | 0.122372 | 0.381758 | 1.623798 | 
| 50 | 0.225866 | 0.720819 | 1.579400 | 7.707926 | 
| 100 | 0.619412 | 2.056454 | 4.555320 | 20.955724 | 
| 500 | 1.784055 | 6.171972 | 11.220639 | 50.669340 | 

We can notice that time consumed roughly grows linearly with total communications(ThreadNum x Loop). And Thus we can estimate that the time needed for one communication is about 0.0005 second.


Below is time(second) consumed when transfering int array[524288](~2Mb) with three hosts crunchy1,crunchy3 and crunchy4 with option -ppn 1 

| Thread Num/ Loop  | 10 | 50 | 100 |  
| --- | --- | --- | --- | 
| 10 | 2.228239  | 9.455117| 18.443947 | 
| 50 | 14.703286 | 72.395926 | 143.868863 | 
| 100 | 28.794298 | 147.561126 | 285.631170 | 

Again the time grows linearly with total communications(ThreadNum x Loop). We can estimate the bandwidth using total data trasfered/time = (100x100x2Mb)/285 = 70Mb/second. 




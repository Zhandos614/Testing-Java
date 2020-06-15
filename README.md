# Exam specification #

You were hired by a company where you have to take over the development of an application. Their predecessor left the company because they were not satisfied with his/her work. The application is made for a customer who takes over the software based on the tests he gives.

## Requirements ##

1. the finished software must conform correctly to the tests received. Do not modify the tests!
2. make software documentation in html format for the software.
3. The finished source must be handed over to the customer in gitlab.
4. tests must run on gitlab, triggered on develop and feature- * branches.

## Notes ##

- the previous programmer may have left errors in the code. If these are found you need to document them in the code and you have to fix them in the hotfixes branch.

- the previous programmer did not complete his/her work, it may contain unfinished functions or he/she may have used wrong basic ideas. If you find one, consult the senior programmer (Zamek) on the slack channel.

- the previous programmer did not document anything, your first task is to understand how the software works. If you run into a problem, consult the senior programmer.

- use the gitflow recommendation during development https://datasift.github.io/gitflow/IntroducingGitFlow.html fix bugs in the hotfixes branch. Whole new development must be in the develop branch.

- Divide among yourself who will write which function. Both programmers should start a feature-xx branch from the develop and work on it until he/she finish the job. Then merge your code into the develop branch.

- all commit must have meaningful speaking content, "I did something" or "first commit" and so on is not acceptable. When you are done with a subtask (a function is done), they are committed to your own feature-xx branch.

- The management of the company wants to see who added what code to the code base. Pay close attention to commit all subtasks to your own feature-xxx branch.
- the deadline for the task is 5 May 2020.

- make a short presentation of the task performed. The presentation can also be a README.md file in the repository root directory. https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet or in a separate sheet in the software documentation.

## Evaluation ##

- if you do not pass the tests, the task is not acceptable.
- if it is not completed by the deadline, the grade will be reduced by one per day.
- if the tests pass, it can be at least mark two, but the final grade depends on the quality of the code and the availability of documentation.
- if you do not follow the gitflow recommendation the grade will be one worse.
- if there is no documentation, the grade will be reduced by one.
- if there is no presentation, the grade will be reduced by one.
- after the completion of the project, we will hold a code-review with the senior programmer, where everyone will protect their own code. The senior programmer has the right to request modifications.

## Correct test result ##

Console:

     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/


Suite: Suite 1
  Test: Open test ...passed
  Test: test ...passed
  Test: Close test ...passed
  Test: Reopen test ...passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      4      0        0
             asserts    118    118    118      0      n/a

Elapsed time =    0.001 seconds


tail -f /var/log/syslog

Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: cannot open file, result:No such file or directory
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository already initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: THREAD TEST
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: cannot open file, result:No such file or directory


# Feladat kiírás #


Önöket alkalmazták egy vállalatnál, ahol át kell venniük egy applikáció fejlesztését. Az elődjük azért távozott a cégtől, mert nem voltak elégedettek a munkájával. Az applikáció egy megrendelő számára készül, aki a szoftvert az általa adott tesztek alapján veszi át.

## Követelmények ##

1. a kész szoftver hibátlanul feleljen meg a kapott teszteknek. A teszteket tilos módosítani!
2. a szoftverhez készüljön szoftver dokumentáció html formátumban.
3. A kész forrást a gitlab-en kell átadni a felhasználónak.
4. a tesztek a gitlab-en fussanak, a develop és a feature-* branch-re triggerelve.

## Megjegyzések ##

- az előző programozó hagyhatott a kódban hibákat is. Ha ezeket megtalálják dokumentálják a kódban és javítsák a hotfixes branch-ben.
- ez előző programozó nem fejezte be a munkáját, lehetnek benne befejezetlen függvények illetve lehet, hogy rossz alapötleteket használt. Ha ilyent találnak konzultáljanak a senior programozóval (Zamek) a slack csatornán.
- az előző programozó semmit sem dokumentált, az első feladatuk megérteni a szofver működését. Ha problémába ütköznek, konzultáljanak a senior programozóval.
- a fejlesztés során használják a gitflow ajánlást https://datasift.github.io/gitflow/IntroducingGitFlow.html a hibákat a hotfixes branch-ban javítsák. Az új fejlesztés a develop branch-ban legyen.
- Osszák ki egymás között, hogy ki melyik függvényt fogja megírni. Mindkét programozó indítson egy feature-xx branch-et a develop-ból és ebben dolgozzon, amíg be nem fejezi a munkát. Ezután merge-eljék a kódjukat a develop branch-be.
- minden commit-nak legyen értelmes beszélő tartalma a "csináltam valamit" nem elfogadható. Ha egy részfeladattal elkészültek (egy függvény kész), akkor commit-olják a saját feature-xx branch-be.
- A cég vezetése látni akarja, hogy ki milyen kódot adott hozzá a kódbázishoz. Fokozottan figyeljenek oda, hogy minden részfeladatot commit-oljanak a saját feature-xxx branch-ükbe.
- a feladat határideje 2020. május 5.
- készítsenek egy rövid prezentációt az elvégzett feladatról. A prezentáció lehet egy README.md file is a repository gyökér könyvtárban, vagy a szoftver dokumentációban egy külön lapon.

## Értékelés ##
- ha a teszteknek nem felel meg, akkor a feladat nem elfogadható.
- ha határidőre nem készül el, akkor naponta eggyel csökken az érdemjegy.
- ha a tesztek lefutnak, akkor legalább kettes lehet, de a végleges érdemjegy függ a kódminőségtől, illetve a dokumentáció meglététől.
- ha nem követi a gitflow ajánlást eggyel rosszabb lesz az érdemjegy.
- ha nincs dokumentáció, akkor eggyel rosszabb lesz az érdemjegy.
- ha nincs prezentáció, akkor eggyel rosszabb lesz az érdemjegy.
- a project elkészülte után code-review-t tartunk a senior programozóval, ahol mindenki a saját kódját védi. A senior programozónak joga van módosításokat kérni. 

## Elvárt test eredmények ##

Console: 

     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/


Suite: Suite 1
  Test: Open test ...passed
  Test: test ...passed
  Test: Close test ...passed
  Test: Reopen test ...passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      4      0        0
             asserts    118    118    118      0      n/a

Elapsed time =    0.001 seconds

tail -f /var/log/syslog

Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: cannot open file, result:No such file or directory
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository already initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: THREAD TEST
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: repository not initialized
Apr 28 21:45:06 ZamekLenovo REPOSITRY TEST[42312]: cannot open file, result:No such file or directory

# Java-test
This is java test project
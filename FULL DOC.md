# 今天绝对要把Git搞清楚！-2022-5-24

## 从本地Git开始讲起

1. 在`/Git-test`目录中开始建立本地git仓库，使用`git init`建立仓库，如下图所示

   ![image-20220524202402253](/Users/mac/Documents/University/Git-doc/Git-test/:Users:mac:Library:Application Support:typora-user-images:image-20220524202402253.png)

2. 加入`README.md`说明文档

3. 在本地git仓库中开始编写代码，编写结束后可以使用`git status`查看git追踪情况，如下图所示

   ![image-20220524202849026](/Users/mac/Documents/University/Git-doc/Git-test/git status.png)

4. 使用`git add <file>`将未追踪的(untracked file)文件加入到当前branch的staging area(暂存区)中，以为后续提交commit作准备。注意，`git add`命令不会真的影响到当前仓库的branch，只是先放到暂存区中，让git知道一会commit需要提交什么。

   ![image-20220524203435838](/Users/mac/Documents/University/Git-doc/Git-test/git add.png)

5. 使用`git commit`进行提交，这样的提交就会在当前branch中创建一个真正的提交(commit)，这个commit可以理解为仓库保存的一个状态，里面有所有文件commit时的样子，也就是说这个commit的作用就有很多：比如下一次commit与这次commit之间的对比，比如以后万一整寄了也可以时空穿梭回来……

   所以所有的commit都有一个独特的编号，可以使用`git log`来查看，如下图所示：

   ![image-20220524203927898](/Users/mac/Documents/University/Git-doc/Git-test/git commit1.png)

   比如这里，创建了2个commit，一个含有`git add.png`(新的)，一个没有(旧的)，那这样就可以通过`git log`来查看：

   ![image-20220524204116683](/Users/mac/Documents/University/Git-doc/Git-test/git log.png)

   这里就看到了2个commit，同时有着commit时的message可以查看，那么如果这时候我想要回到没有`git add.png`的时候（时光倒流），那就可以使用`git checkout <commit_id>`回到那个commit的状态，而为了演示方便，顺便介绍branch的功能，我们可以用`git checkout -b <name> <commit_id>`来开一个新的branch分支，让那个分支的状态就是想要回到的那个commit的状态：

   别急，正好这里整错了，也记录一下：

   ![image-20220524204757690](/Users/mac/Documents/University/Git-doc/Git-test/branch失误.png)

   看看，这里刚才敲了什么命令？`git checkout -b db10d`，这里的`db10d`是commit id，但是你tm没起名字啊，就创建了一个名叫`db10d`的分支，那现在就要把它删了，就应当使用`git branch -d <branch_name>`来删除那个分支。好，下面继续时光倒流：

   ![image-20220524210052798](/Users/mac/Documents/University/Git-doc/Git-test/时光倒流.png)

   😄，成功喵！可以看到我们在`no-pic`这个branch里，是没有`git add.png`这个图片的，说明我们确实回来了，✌️。

   下面回到`master`分支，可以看到`git add.png`又出现了

   ![image-20220524212123900](/Users/mac/Documents/University/Git-doc/Git-test/回到现在.png)

   OK，现在commit差不多讲完了，以后如果还有补充会加到这里



## GitHub远程仓库与本地git仓库的关联

1. 本地git仓库已经很好用了，但我们肯定要OPEN SOURCE！那就得把我们的仓库关联到在线仓库，好。

先在GitHub上创建一个仓库：

![image-20220524213206184](/Users/mac/Documents/University/Git-doc/Git-test/创建远程仓库.png)

正如图片里所说，可以使用`git remote add <远程仓库在本地git仓库的名字> <远程仓库的git链接>`来把远程仓库的reference加到本地git仓库里，所以到时候我们如果想把commit(提交)同步到远程仓库的时候，就可以用这个`<远程仓库在本地git仓库的名字>`来push：

2. 下面使用`git push -u origin master`来把`master`分支的状态，`同步`到`origin`这个远程reference里，而`-u`这个选项代表以后在`master`分支中的`push`操作都默认同步到`origin`这个远程reference里，也就是说，`git push -u origin master`和`git push --set-upstream origin master`等价。而如果没有`-u`或者`--set-upstream`的话，就得每次`git push <远程reference> <要同步到远程的branch>`了。

![image-20220524213719552](/Users/mac/Documents/University/Git-doc/Git-test/push到远程仓库.png)

可以看到成功把当前分支master同步到了远程仓库里。注意这里的信息：

`*[new branch] master -> master`就表示在远程仓库里新创建了一个名字叫`master`的分支，然后这里把``本地的master`分支状态同步到了`远程的master`分支。

`Branch 'master' set up to track remote branch 'master' from 'origin'.`表示`本地的master`分支已经设定为和`远程reference的origin`中的`远程的master`分支建立了追踪联系，以后在`本地的master`分支中，执行的`git push`就等价于执行了`git push origin master`了。👌

3. 那么如果我有多个分支，比如master是最终版本，然后我想加一个新的功能，我开了一个名叫`new-feature`的分支，新建分支是用`git checkout -b <new_branch_name>`，注意，如果直接使用这条命令，那就是相当于创建了一个新的分支，其状态和“创建分支的分支”一样，比如我现在是处于`master`分支里，我使用了`git checkout -b new-feature`，那么这个`new-feature`分支的状态，就是等同于我`master`的状态，但是之后`master`和`new-feature`之间就没关系了。

   如下图：![image-20220524223946055](/Users/mac/Documents/University/Git-doc/Git-test/新分支.png)



4. 下面谈谈`merge`的问题，我们现在的分支是这样的：

![IMG_B3EB195673FF-1](/Users/mac/Documents/University/Git-doc/Git-test/git merge.png)

好，我们现在来尝试一下：

![image-20220524231331770](/Users/mac/Documents/University/Git-doc/Git-test/merge1.png)

这里对`test.c`进行了一些修改，同时因为只修改了一个文件，那么就可以用`git commit -am "<message>"`来直接跳过`git add <file>`的步骤直接commit(提交)

![image-20220524231527400](/Users/mac/Documents/University/Git-doc/Git-test/merge2.png)

现在又对`test.c`进行了一次修改并提交，就和上面的图里描述的场景一样了，下面我们要测试两种不同情况的`merge`，分别是有冲突的和无冲突的。

 1. 如果是有冲突的merge，是什么情况呢？这里我们再开一个分支`master-copy`把当前master分支的状态复制一份，同时对`master-copy`里的`test.c`来进行一些修改(**修改了同一行！**)。那么此时如果在`master-copy`中想要`git merge new-feature`的话，就会出现冲突，即`master-copy`当前状态里的`test.c`和`new-feature`当前状态里的`test.c`都是从`master`分支里复制过来并进行了一些修改的文件了，如果现在要把`new-feature`分支合并到`master-copy`分支中，你说合并完后`test.c`里的内容听谁的？听`master-copy`的，还是听`new-feature`的？那么我们就需要来处理这个冲突问题：

    现在使用`git diff <branch_name>`来在`master-copy`分支中检查和`new-feature`分支的不同：

    ![image-20220524232337772](/Users/mac/Documents/University/Git-doc/Git-test/git diff.png)

    可以看两个分支都对原本的`test.c`进行了修改，原本只有`printf("Hello world\n");`这一句的，所以下面来尝试进行一下`git merge <branch_name>`:

    ![image-20220524232520729](/Users/mac/Documents/University/Git-doc/Git-test/conflict.png)

    可以看到git的`Auto-merging`失败了，说有冲突，那么下面就得解决冲突，怎么解决呢？

    这时候我们再打开引起冲突的那个文件`test.c`，可以看到git帮我们标注了冲突的位置：

    ![image-20220524233046879](/Users/mac/Documents/University/Git-doc/Git-test/merge3.png)

    从`<<<<<<< HEAD`到`=======`是当前分支（这里也看出来，git里HEAD就是当前分支的意思）对`test.c`所做的修改，而从`=======`到`>>>>>>> new-feature`则是`new-feature`分支对`test.c`所做对修改。那么我们就需要把冲突解决：

    ![image-20220524233536971](/Users/mac/Documents/University/Git-doc/Git-test/solve conflict.png)

    这里我把标注冲突的符号删除，保留了`master-copy`中的一些修改和`new-feature`中的一些修改，我认为这样是两者共存的一种解决方案，那么此时就认为，冲突解决了，我们再查看`git status`和`git diff`:

    ![image-20220524233808530](/Users/mac/Documents/University/Git-doc/Git-test/solve merge2.png)

    那么在冲突解决之后，我们的`test.c`相当于是融合了`master-copy`分支和`new-feature`分支的修改，就需要在当前分支`master-copy`再进行一次commit(提交)：

    ![image-20220524233947142](/Users/mac/Documents/University/Git-doc/Git-test/merge ok.png)

    这样我们的有冲突的`merge`就搞定了。

    2. 无冲突的`merge`，更简单了，连冲突都不用管，直接`git merge <branch_name>`把需要合并的分支合并到当前分支里来就ok了。

    

    

    5. 下面来说所谓的PR，也就是`pull request`到底是个啥。

       我们说如果一个仓库有许多人在用，那么很显然只有管理员才可以对主分支进行各种操作（就比如上面的`merge`等），而比方说有一个人是搞A功能的，他自己`git clone`下来了仓库后，开了一个分支叫`func-A`，然后在里面搞开发，一直写一直写，终于有一天，他觉得这个功能OK了，可以合并到主分支里了，但是很显然这个*赛博搬运工*并没有主分支的管理权限，他肯定不能在主分支去做`git merge`这类操作，那怎么办呢？这个时候，就是`pull request`大显身手的地方了。

       `pull request`这个名字，前面是`pull`：我们知道，`git pull`是拉取远程仓库中分支的最新内容同步到本地仓库；后面是`request`：英文含义是 请求 ，那么很显然，所谓的PR就是先**拉取**分支同步之后，你又做了一些修改，然后**请求**仓库的管理员来`merge`你的这个分支。这就是PR。

       好，那么我们就来实践一下：

       ![image-20220524234937602](/Users/mac/Documents/University/Git-doc/Git-test/func-a branch.png)

       ![image-20220524234925213](/Users/mac/Documents/University/Git-doc/Git-test/func-a.png)

       我们写好了A功能，现在我们肯定没有`merge`权限，那就只能`git push origin func-A`咯，这里前提是你已经把远程reference设置好了：

       ![image-20220524235117820](/Users/mac/Documents/University/Git-doc/Git-test/PR.png)

       可以看到，你现在的这个`git push origin func-A`实际上是在远程仓库里新建了一个名叫`func-A`的分支，同时git也提示你可以用一个链接🔗去创建一个`pull request`，我们就试试看：

       ![image-20220524235438071](/Users/mac/Documents/University/Git-doc/Git-test/创建PR.png)

       就是向仓库提交了一个`request`，想让管理员去`merge`，所以管理员在GitHub上就能看到这样的信息：

       ![image-20220524235531262](/Users/mac/Documents/University/Git-doc/Git-test/GitHub看到的PR.png)

       那么如果管理员认为是ok的，就会去`merge`你的这个分支到主分支去，你滴任务就完成啦哈哈哈哈！

       同时如果管理员确实`merge`了，你的这个为了创建PR而通过`git push origin func-A`在远程仓库创建出来的`func-A`分支的使命也就到此结束了，管理员就会给你把分支删了，而你则可以通过`git pull`拉取最新的主分支，就能看到你的修改已经被接受了，高不高兴？

       ![image-20220524235829761](/Users/mac/Documents/University/Git-doc/Git-test/delete PR分支.png)

       只能说很牛了，tm又犯病了，test.c没commit就push上去了，你可真是个人才啊伙计。

       ![image-20220524235955992](/Users/mac/Documents/University/Git-doc/Git-test/分支没保存更改就该分支.png)

       也好，看看现在是什么问题，`test.c`没有commit就push，会出现2个问题：

       首先是`test.c`tm里面的A函数根本没进到主分支里（说明管理员也是nt）

       ![image-20220525000434485](/Users/mac/Documents/University/Git-doc/Git-test/testc根本没修改.png)

       其次就是，你现在想要回到`master`分支去做事的话，git就会提示你说，你要是现在回去了，你刚才辛辛苦苦写的`test.c`就tm全没了！所以要么进行一次commit提交，要么使用`git stash`来暂存，暂存的事情我们“今天”再聊（现在是2022-5-25 0:03）

       ![image-20220525000349640](/Users/mac/Documents/University/Git-doc/Git-test/重新PR.png)

       好，又进行了一次提交，现在又在远程仓库创建了一个，为了创建PR的分支，`func-A`，去创建PR吧孩子！

       好了，让我们再看看主分支有没有修改吧：

       ![image-20220525000646509](/Users/mac/Documents/University/Git-doc/Git-test/成功funcA.png)

       好家伙，真是错误频出，回到主分支后，别忘了先`git pull`来拉取最新的远程主分支啊（刚才不是才接受了一个funcA吗？），如果不`git pull`就`git push`，看看什么鬼样！

       ![image-20220525000852633](/Users/mac/Documents/University/Git-doc/Git-test/没pull就push.png)

       而在`git pull`的时候，就可以看到远程主分支的修改了：

       ![image-20220525000953705](/Users/mac/Documents/University/Git-doc/Git-test/远程主分支修改.png)


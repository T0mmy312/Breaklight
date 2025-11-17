# Git Tutorial

## One commit (small change on a brach)

The main process is:
``` sh
git add . # stage the changes for commit
git pull # pull possible changes from the brach to resolve merges
git commit -m "message here" # commit changes to branch
git push # push changes to branch
```
### Possible Problems


#### merging

For example, if user1 makes a change to `main.cpp`, commits, and pushes it, and another person also changes `main.cpp,` stages the change with `git add`, and then tries to pull, the following error can occur (which is normal and to be expected):

```
user2> git pull
remote: Enumerating objects: 5, done.
remote: Counting objects: 100% (5/5), done.
remote: Total 3 (delta 0), reused 3 (delta 0), pack-reused 0 (from 0)
Unpacking objects: 100% (3/3), 245 bytes | 27.00 KiB/s, done.
From github.com:T0mmy312/GitBranchExample
   debf290..c878670  main       -> origin/main
Updating debf290..c878670
error: Your local changes to the following files would be overwritten by merge:
        main.cpp
Please commit your changes or stash them before you merge.
Aborting
```

When this error occurs, it means someone changed the file you edited, and Git cannot combine the changes into one file without your help.

To fix this, you first have to store your changes, pull the conflicting changes, then apply your changes again and resolve conflicts:

``` sh
git stash # store changes in the stash
git pull # get the conflicting changes from github
git stash pop # apply the stored changes to your file
```

After doing this, you will most likely see a message indicating there is a conflict that can’t be resolved automatically:

```
user2> git stash pop
Auto-merging main.cpp
CONFLICT (content): Merge conflict in main.cpp
On branch main
Your branch is up to date with 'origin/main'.

Unmerged paths:
  (use "git restore --staged <file>..." to unstage)
  (use "git add <file>..." to mark resolution)
        both modified:   main.cpp

no changes added to commit (use "git add" and/or "git commit -a")
The stash entry is kept in case you need it again.
```

Under `Unmerged paths:` you can see all the files with conflicting changes — in this case `main.cpp`.

From here it splits into two paths depending on what you want: either you keep your change, use their change (from the commit you’re pulling), or resolve the merge manually if you want to keep parts of both.

**1. Resolve manualy** 

To resolve these conflicts, open `main.cpp` (or your conflicting file) and find the conflict markers, which look like this:

```
<<<<<<< Updated upstream
user1 change 
=======
user2 change 
>>>>>>> Stashed changes
```

If you have the Git VS Code extension, it will show you options to choose from. If not, you can manually edit this part of the code.

- The code between `<<<<<<< Updated upstream` and `=======` is the code from the commit you are trying to pull (in this case `user1 change` as a placeholder).

- The code between `=======` and `>>>>>>>` Stashed changes is the code you made (`user2 change`).

To resolve this manually, you can delete the entire block, keep the incoming change, keep your change, or merge parts of both — just make sure to remove Git’s conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`).

When you are finished, add your changes with:

``` sh
git add .
```

This will mark the conflicts as resolved, and you can then commit and push like before.

**2. Choose one of the changes**

If you simply want to use one of the changes, you can do this:

``` sh
git checkout --ours main.cpp # use the version from the commit your pulling
git chackout --theirs main.cpp # use your version of main.cpp
```

It may seem a bit wierd that `--theirs` is the version you stashed, but because you first stashed and temporaily removed the changes then pulled successfully, the incoming change is then the change applied from your stash which is labled as `--theirs`.

Once you’ve chosen for each conflicting file, just add your changes to mark the conflict as resolved and commit like before.

## Multiple commits (creating a new Branch)

When you want to make a big change or something independent that you want to add to the main branch later, you can create a branch. To create your branch, you can do the following:

``` sh
git branch yourBranch # create a branch with the name yourBranch
git switch yourBranch # go to the branch yourBranch
``` 

Now you should be on your new branch.

Make sure that the first time you push a change on this new branch, you do the following:

```sh
git push -u origin yourBranch # push yourBranch to the github (origin)
```

If you don’t do this, you will get an error, and the branch won’t appear on GitHub or for anyone else.

From now on, you can follow the One commit process above to commit to that branch.

If you forget which branch you’re on or want to check all available branches, you can run:

``` sh
git branch -a
```

You will get something like this:

```
user2> git branch -a
  main
* yourBranch
  remotes/origin/HEAD -> origin/main
  remotes/origin/main
```

(You can ignore `remotes/origin/HEAD -> origin/main` and `remotes/origin/main`)

The branch with the `*` is the one you are currently on.

If you want to switch branches anytime to work on other parts of the project, just use `git switch` like above.

Now the only problem is: if you are finished with development, how do you get your changes back to main? The answer is merging.

### Merging

Merging means applying all the changes from your branch to the main branch, or to another branch if branched from it.

To merge, you have to go to the branch you want to merge into and do the following:
``` sh
git merge yourBranch
```

if conflicts occour, just follow the above merging tutorial.
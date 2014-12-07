# Some basic commands for using git with a remote svn repo and vice versa
# Don't just run this, actually read it. 
# ** You have been warned **

# ==== SET UP REMOTE SVN REPO FOR LOCAL GIT REPO ====

# (1) Change to a harmless folder, like your home directory (i.e. NOT your cwd)
# Checkout the svn you want to add your code to and make a folder, if you haven't done this
# already

svn co protocol://path/to/folder
cd folder
mkdir myFolder
mkdir myFolder/branches
mkdir myFolder/tags
mkdir myFolder/trunk
svn commit -m "Added some folders for the repo"

# (2) Go back to your current git repo and check eveything is up to date 

cd path/to/local/git/repo
git status
do all the commits
push them to your other remotes

# (3) Initialise

git svn init -s --prefix=svn/ protocol://path/to/folder #The prefix allows one to specify a prefix which is prepended to the names of remotes if trunk/branches/tags are specified. So now trunk will be svn-trunk. There is no return statment.

#To check this worked and get the current revision number:
svn info protocol://path/to/folder 

#Output: 
# URL: protocol://path/to/folder
# Repository Root: svn+ssh://user@svn.cern.ch/reps/atlasinst
# Repository UUID: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
# Revision: nnnnnn
# Node Kind: directory
# Last Changed Author: name
# Last Changed Rev: nnnnnn-1
# Last Changed Date: yyyy-mm-dd xx:xx:xx -xxxx0 (day, xx Month Year)

# (4) Fetch the svn 

git svn fetch -r###### #where # represents the revision number from the last command

# (5) Now we use branches! First look at the current branches:

git branch -av #-a = including remote, -v= verbose

#Output:
#* master                10e9d57 SVN testing   <---- my local repo
#  remotes/origin/HEAD   -> origin/master      <---- my bitbucket repo
#  remotes/origin/master 10e9d57 SVN testing   <---- my github repo
#  remotes/svn/trunk     1f74b17 New folders   <---- my new svn repo

# (6) Now we create a new branch alias for commits to the svn (only need to do this once!)

git checkout -b svn-trunk remotes/svn/trunk

#From hereonin you can simply write: git checkout svn-trunk

# (7) Rebase, merge, decommit

git svn rebase
git merge master #or whatever branch you want to commit to the svn
git svn dcommit

# (8) Switch back to the working branch!

git checkout master


#===========================================================================================

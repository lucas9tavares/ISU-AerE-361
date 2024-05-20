# Git Workflow

## Git

1. Open a Terminal in your virtual machine Linux environment.

2. In the command line, insert the following lines to tell Git your name and add your email address:

'''
git config --global user.name "lucas9tavares"
git config --global user.email "7lucastavares@gmail.com"
'''

3. Make sure you are on the right directory you want to copy the Git repository in by using the 'pwd' command.

4. Generate a Token of Security through Github.com. You will use it as your password in the command line.

5. Now, go to the desired repository page on Github.com. On the top right corner of the screen, click on a green buttom, from where you will be able to retrieve the HTTPS URL to clone your repository into your local Linux directory.

6. Back on the command line, insert 'git clone' and the URL copied from Github.com

'''
git clone https://github.com/AERE-361/lab-1-lucas9tavares.git
'''

	_Useful reminder: ctrl + C and ctrl + V are note copy and paste shortcuts_

7. You will be prompted for your username and password for security uthentication. You your Github username and the Token you previously generated as the password.

8. Some useful commands are 'git status', which will ask Git the status of our current repository, and 'git clean -f && git reset --hard', which will remove new files and reset modifications to the state they were when cloned.

9. To create a new branch, use 'git branch', and to move over to the new branch use 'git checkout'. For example, for a new branch named develop use:

'''
git branch develop
git checkout develop
'''

10. To create a new text file named foo use 'emacs foo.txt'. Type the text and save the file. You can use .md for a Markdown file.

11. To save your work, you first need to add the new or modified files and then commit them. You should also comment in your commit for better documentation.

'''
git add foo.txt
git commit -m "Created foo.txt"
'''

	**Always commit your work when possible. You don't want to loose unsaved progress**

12. To send your work back to Git (where you will have a backup of your work and others working on the same repository will be able to see and access your progress), first make sure all your work is committed and that we are on the develop branch where all the work was made. Then insert:

'''
git push origin develop
'''

Git will ask for authentication. Re-enter the username and Token.

## Importance of Good Documentation

Documentation is always important so when something new happened or is developed, documentation will help explain and describe this event, new idea or creation. A good documentation is essential for others and even for future us to understand what we did in that code, project, or file when we were developing it. In our AerE 361 classroom environment, we need to make sure our assignments are well documented so that the professor and the TAs can understand and grade our work, and the future us are able to comprehend what was our though process and how we did this and that, so we can apply this knowledge or even the entire code to other projects or assignments.
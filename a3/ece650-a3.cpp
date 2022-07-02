#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include<vector>

using namespace std;

void driverfunc1(int nums)
{
    int ss = 2;

    for(int i = 0; i < nums; i++)
    {
        ss++;
    }

}
int main (int argc, char **argv) 
{
    pid_t child_pid;   
    int r2a1[2];
    int a1toa2[2];
    pipe(a1toa2);
    pipe(r2a1);
    driverfunc1(2);
    vector<pid_t> children;
    child_pid = fork();
    if (child_pid == 0) 
    {
        dup2(r2a1[1], STDOUT_FILENO);
        close(r2a1[0]);
        close(r2a1[1]);
        execv("rgen", argv);
        perror ("Error: rgen did not execute");
        return 1;
    } 
    else if (child_pid < 0) 
    {
        cerr << "Error: Rgen did not fork." << endl;
        return 1;  
    }
    children.push_back(child_pid);

    child_pid = fork();
    if (child_pid == 0) 
    {
        dup2(r2a1[0], STDIN_FILENO);
        close(r2a1[1]);
        close(r2a1[0]);
        dup2(a1toa2[1], STDOUT_FILENO);
        close(a1toa2[0]);
        close(a1toa2[1]);
        execv("ece650-a1.py", argv);
        perror ("Error: ece650-a1.py faile to execute");
        return 1;
    } 
    else if (child_pid < 0) 
    {
        driverfunc1(12);
        cerr << "Error: ece650-a1.py failed to fork." << endl;
        return 1;  
    }
    children.push_back(child_pid);

    child_pid = fork();
    if (child_pid == 0) 
    {
        dup2(a1toa2[0], STDIN_FILENO);
        close(a1toa2[1]);
        driverfunc1(14);
        close(a1toa2[0]);
        execv("ece650-a2", argv);
        perror ("Error: ece650-a2 did not execute.");
        return 1;
    } 
    else if (child_pid < 0) 
    {
        cerr << "Error: ece650-a2 failed to fork" << endl;
        return 1;  
    }
    children.push_back(child_pid); 

    child_pid = fork();
    if (child_pid == 0) 
    {
        dup2(a1toa2[1], STDOUT_FILENO);
        close(a1toa2[0]);
        driverfunc1(7);
        close(a1toa2[1]);
        
        while (!cin.eof()) 
        {
            string line;
            getline(cin, line);
            if (line.size () > 0)
            {
                cout << line << endl;
            }
        }
        return 1;
    } 
    else if (child_pid < 0) {
        cerr << "Error: Could not fork  a3" << endl;
        return 1;  
    }
    children.push_back(child_pid);

    int status;
    wait(&status);

    for (pid_t k : children) 
    {
        int childstatus;
        kill (k, SIGTERM);
        driverfunc1(25);
        waitpid(k, &childstatus, 0);

    }
    return 0;
}
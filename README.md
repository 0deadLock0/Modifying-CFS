
**NOTE:** All the changes are made on linux-5.9.1.

# CFS Modification::

Added Attribute-

- rt_nice of type 64 bit unsigned int in the sched_entity structure


## Modifying Files-

The following files are modified in order to change the working of the CFS-

- linux-5.9.1/include/linux/sched.h, to add the new attribute to the sched_entity structure

- linux-5.9.1/kernel/sched/core.c, to initialise the new added attribute when a new task is created(in the '__sched_fork' function)

- linux-5.9.1/kernel/sched/fair.c, to modify the functions responsible for selection criteria


## Functions modified to change CFS working-

NOTE: All these fucntions are present in linux-5.9.1/kernel/sched/fair.c only

- 'entity_before' to check which process should appear first between two process.

- 'update_curr' to update the details of the process which is latestly run by the CFS.

## Modified Selection Criteria-

In place of the usual vruntime, the first criteria for selection is now rt_nice.

If there are two processes with rt_nice values as following, then:

First_process		Second_process	Favourability_in_Scheduling

  rt_nice = 0		  rt_nice = 0		ON THE BASIS OF THE VRUNTIME

  rt_nice = 0		  rt_nice > 0			Second_process

  rt_nice > 0		  rt_nice > 0		process with larger rt_nice

Vruntime is checked only when both processes has zero rt_nice values.

**NOTE:**

By default, the rt_nice value of a process is zero and can only be modified by using the rtnice system call, which is currently nowhere called automatically and can only be called deliberately by the user.

Hence the normal working of scheduler is preserved, thus adding the new attribute rt_nice has no ill affects on normal working of the system.


## Syscall::

**Functioning-**

The system call is named rtnice it takes two parameters, a int and a long as pid of the process and it's realtime gaurantee respectively.

It syscall number is 548.

It first checks if the given realtime requirenment isn't negative.

Then it checks if the given pid, corressponds to an actuall process or not.

If everything, goes fine it set the rtnice attribute of the process with the following pid to the desired realtime requirenment.

The details of this modification is written to the kernel log for user accessibility and ease.

On kernel log the name of the process whoose rt_nice has been modified is printed alongwith it's old rt_nice and it's current rt_nice.

**Error Handling-**

- The given pid do not correspond to a process

- The provided realtime requirenment (rt_nice) is negative

**Return Value-**
 0 : For successfull running

 1 : For unsuccessful running due to Errors


## Patching::

- Run the command "patch -p0 < diff.txt" in the folder containing the downloaded linux folder

**NOTE:**

Add --dry-run flag to check if the patch is working without doing the changes.

Add -R flag to undo the changes made by patch


**Testing the Changes made::**

- Run the test.c file using the Makefile provided, after rebuilding the kernel

**NOTE:** The system should be running on a single core to observe the changes


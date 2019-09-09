#import <stdio.h>

#import <mach/mach.h>
#import <mach/error.h>
#import <mach/message.h>

#import <CoreFoundation/CoreFoundation.h>

kern_return_t mach_vm_read(vm_map_t target_task, mach_vm_address_t address, mach_vm_size_t size, vm_offset_t *data, mach_msg_type_number_t *dataCnt);
kern_return_t mach_vm_read_overwrite(vm_map_t target_task, mach_vm_address_t address, mach_vm_size_t size, mach_vm_address_t data, mach_vm_size_t *outsize);
kern_return_t mach_vm_write(vm_map_t target_task, mach_vm_address_t address, vm_offset_t data, mach_msg_type_number_t dataCnt);
kern_return_t mach_vm_allocate(vm_map_t target, mach_vm_address_t *address, mach_vm_size_t size, int flags);
kern_return_t mach_vm_deallocate(vm_map_t target, mach_vm_address_t address, mach_vm_size_t size);

#define PROC_PIDPATHINFO_MAXSIZE  (4 * MAXPATHLEN)
int proc_pidpath(pid_t pid, void *buffer, uint32_t buffersize);

#define TF_PLATFORM 0x400

#define CS_VALID                        0x0000001    /* dynamically valid */
#define CS_ADHOC                        0x0000002    /* ad hoc signed */
#define CS_GET_TASK_ALLOW               0x0000004    /* has get-task-allow entitlement */
#define CS_INSTALLER                    0x0000008    /* has installer entitlement */

#define CS_HARD                         0x0000100    /* don't load invalid pages */
#define CS_KILL                         0x0000200    /* kill process if it becomes invalid */
#define CS_CHECK_EXPIRATION             0x0000400    /* force expiration checking */
#define CS_RESTRICT                     0x0000800    /* tell dyld to treat restricted */
#define CS_ENFORCEMENT                  0x0001000    /* require enforcement */
#define CS_REQUIRE_LV                   0x0002000    /* require library validation */
#define CS_ENTITLEMENTS_VALIDATED       0x0004000

#define CS_ALLOWED_MACHO                0x00ffffe

#define CS_EXEC_SET_HARD                0x0100000    /* set CS_HARD on any exec'ed process */
#define CS_EXEC_SET_KILL                0x0200000    /* set CS_KILL on any exec'ed process */
#define CS_EXEC_SET_ENFORCEMENT         0x0400000    /* set CS_ENFORCEMENT on any exec'ed process */
#define CS_EXEC_SET_INSTALLER           0x0800000    /* set CS_INSTALLER on any exec'ed process */

#define CS_KILLED                       0x1000000    /* was killed by kernel for invalidity */
#define CS_DYLD_PLATFORM                0x2000000    /* dyld used to load this is a platform binary */
#define CS_PLATFORM_BINARY              0x4000000    /* this is a platform binary */
#define CS_PLATFORM_PATH                0x8000000    /* platform binary by the fact of path (osx only) */

#define CS_DEBUGGED                     0x10000000  /* process is currently or has previously been debugged and allowed to run with invalid pages */
#define CS_SIGNED                       0x20000000  /* process has a signature (may have gone invalid) */
#define CS_DEV_CODE                     0x40000000  /* code is dev signed, cannot be loaded into prod signed code */

extern mach_port_t tfp0;
extern uint64_t kernel_base;
extern uint64_t kernel_slide;

extern uint64_t offset_kernel_task;
extern uint64_t offset_zonemap;
extern uint64_t offset_add_ret_gadget;
extern uint64_t offset_osboolean_true;
extern uint64_t offset_osboolean_false;
extern uint64_t offset_osunserializexml;
extern uint64_t offset_smalloc;

uint64_t find_port(mach_port_name_t port);

uint64_t proc_find(pid_t pid);
void kern_utils_cleanup(void);

void platformize(uint64_t proc);
void fixup(pid_t pid);
void fixup_setuid(pid_t pid, uint64_t proc);
void fixup_sandbox(uint64_t proc);
void fixup_cs_valid(uint64_t proc);
void fixup_get_task_allow(uint64_t proc);


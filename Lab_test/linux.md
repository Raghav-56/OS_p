# Linux File Permission Commands

Linux commands that allow us to change file permissions

## List of File Permission Commands

- `chmod`: Change mode (permissions) of files and directories
- `chown`: Change owner of files and directories
- `chgrp`: Change group ownership of files and directories
- `ls -l`: List files with permissions information

## Command Details

### chmod

**Purpose:** Change permissions of files and directories

**Syntax:**
```bash
chmod [options] [permissions] [file]
```

**Major Options:**
- `-R, --recursive`: Change permissions recursively for directories and their contents
- `-v, --verbose`: Display a diagnostic message for every file processed

#### Understanding Unix/Linux File Permissions

In Linux, each file and directory has three user classes:
- **Owner/User**: The user who created the file or directory
- **Group**: The group of users with specified permissions
- **Others**: Everyone else on the system

Each user class can have the following permissions:
- **Read (r)**: View file contents or list directory contents
- **Write (w)**: Modify file contents or create/delete files within a directory
- **Execute (x)**: Run the file as a program or access files within a directory

#### Symbolic Notation

Symbolic notation uses letters and symbols for more intuitive permission changes:
- **User categories:** `u` (user/owner), `g` (group), `o` (others), `a` (all users)
- **Operations:** `+` (add permission), `-` (remove permission), `=` (set exact permission)
- **Permissions:** `r` (read), `w` (write), `x` (execute)

**Examples:**

1. **Add execute permission for owner:**
```bash
chmod u+x script.sh
```
This adds execute permission for the file owner while keeping other permissions unchanged. Essential for making shell scripts executable.

2. **Remove write permission for others:**
```bash
chmod o-w file.txt
```
This removes write permission for others without changing other permissions. Important for securing sensitive files.

3. **Set read and execute permissions for all:**
```bash
chmod a=rx filename
```
This sets exact permissions (read and execute only) for user, group and others, removing any other permissions that might exist.

4. **Add write permission for owner and read permission for group and others:**
```bash
chmod u+w,go+r filename
```
This adds specific permissions to different user categories in a single command.

#### Numeric (Octal) Notation

Numeric notation uses 3 or 4 digits in base-8 (octal) format where each digit represents permissions for a user class:
- First digit (optional): Special permissions (setuid, setgid, sticky bit)
- Second digit: Owner permissions
- Third digit: Group permissions
- Fourth digit: Others permissions

Each permission has a specific value that can be combined:
- Read (r) = 4
- Write (w) = 2
- Execute (x) = 1

The digit for each user class is calculated by adding these values together.

**Examples with detailed explanations:**

1. **Set rwx for owner, rx for group and others:**
```bash
chmod 755 filename
```
This sets permissions to:
- Owner: rwx (4+2+1 = 7) → Full control
- Group: rx (4+1 = 5) → Can read and execute but not modify
- Others: rx (4+1 = 5) → Can read and execute but not modify

2. **Set rw for owner, r for group and others:**
```bash
chmod 644 filename
```
This sets permissions to:
- Owner: rw (4+2 = 6) → Can read and write
- Group: r (4) → Can only read
- Others: r (4) → Can only read

3. **Full permissions for owner only:**
```bash
chmod 700 filename
```
This gives:
- Owner: rwx (4+2+1 = 7) → Full control
- Group: --- (0) → No access
- Others: --- (0) → No access

#### Special Permissions

Special permissions add additional functionality beyond the basic read, write, and execute:

- **setuid (4000)**: When set on an executable file, the program runs with the permissions of the file owner instead of the user executing it.
  ```bash
  chmod 4755 filename  # Sets setuid bit and 755 permissions
  ```
  
- **setgid (2000)**: When set on an executable file, the program runs with the permissions of the file group. When set on a directory, new files created inherit the directory's group.
  ```bash
  chmod 2755 filename  # Sets setgid bit and 755 permissions
  ```
  
- **sticky bit (1000)**: When set on a directory, files within can only be deleted or renamed by their owner, the directory owner, or root.
  ```bash
  chmod 1777 /shared_directory  # Sets sticky bit and 777 permissions
  ```

#### Recursive Permission Changes

To change permissions for all files and directories within a directory structure:
```bash
chmod -R [permissions] directory
```

**Practical recursive examples:**
```bash
chmod -R +x *.sh directory/  # Make all scripts executable
chmod -R go-w directory/     # Remove all write permissions for group and others
```

### chown

**Purpose:** Change the owner and/or group of files or directories

**Syntax:**
```bash
chown [options] [owner][:group] file
```

**Major Options:**
- `-R, --recursive`: Change ownership recursively through directories
- `-v, --verbose`: Output a diagnostic for every file processed

**Basic Usage Examples:**

1. **Change file owner:**
```bash
chown user1 file.txt
```
This changes the owner of file.txt to user1 without modifying the group ownership.

2. **Change owner and group simultaneously:**
```bash
chown user1:group1 file.txt
```
This changes both the owner to user1 and the group to group1 in a single command.

3. **Change only the group using chown:**
```bash
chown :group1 file.txt
```
This changes only the group to group1 while keeping the current owner.

4. **Change ownership recursively:**
```bash
chown -R user1:group1 directory/
```
This changes the owner and group of the directory and all files and subdirectories within it.

**Real-world applications:**

- **After user account migration:**
  ```bash
  chown -R newuser:newgroup /home/olduser
  ```

- **Fixing ownership after restoring backups:**
  ```bash
  chown -R www-data:www-data /var/www/html
  ```

### chgrp

**Purpose:** Change the group ownership of files or directories

**Syntax:**
```bash
chgrp [options] group file
```

**Major Options:**
- `-R, --recursive`: Change group ownership recursively
- `-v, --verbose`: Output a diagnostic for every file processed

**Basic Usage Examples:**

1. **Change file group:**
```bash
chgrp developers file.txt
```
This changes the group of file.txt to 'developers' while keeping the current owner.

2. **Change group recursively:**
```bash
chgrp -R developers project/
```
This changes the group of the project directory and all files and subdirectories within it.

### ls -l

**Purpose:** List files with detailed information including permissions

**Syntax:**
```bash
ls -l [options] [file/directory]
```

**Major options with -l:**
- `-a`: Show hidden files (those starting with .)
- `-h`: Show file sizes in human-readable format (KB, MB, etc.)
- `-R`: List subdirectories recursively

**Understanding the output:**

Example output:
```
-rw-r--r-- 1 user group 1234 Jan 1 12:00 file.txt
drwxr-x--- 2 root admin 4096 Mar 15 10:30 private_dir
lrwxrwxrwx 1 user group   12 Feb 20 15:45 link -> original.txt
```

Detailed breakdown of each field:

1. **First character - File type:**
   - `-`: Regular file
   - `d`: Directory
   - `l`: Symbolic link
   - Others: Special file types

2. **Characters 2-10 - Permissions:**
   - Characters 2-4: Owner permissions (rwx)
   - Characters 5-7: Group permissions (rwx)
   - Characters 8-10: Others permissions (rwx)
   
   Special indicators may appear in the permission fields:
   - `s` in owner/group execute position: setuid/setgid
   - `t` in others execute position: sticky bit

3. **Hard link count:** Number of hard links to the file/directory

4. **Owner name:** Username of the file owner

5. **Group name:** Group name of the file

6. **File size:** Size in bytes (or human-readable with -h)

7. **Modification time:** Date and time the file was last modified

8. **File name:** Name of the file or directory

**Examples of common commands:**
```bash
ls -l                   # List current directory with permissions
ls -la                  # List all files including hidden ones
ls -lh                  # List with human-readable file sizes
```

### Practical Applications

- **Securing configuration files:** 
  ```bash
  chmod 600 config.ini
  ```
  Only owner can read/write, ideal for files with sensitive data.

- **Making scripts executable:** 
  ```bash
  chmod +x script.sh
  ```
  Adds execute permission while preserving existing permissions.

- **Restricting directory access:** 
  ```bash
  chmod 750 documents/
  ```
  Full access to owner, read/execute for group, nothing for others.

- **Setting up a shared directory:** 
  ```bash
  chmod 775 shared/
  chgrp team shared/
  ```
  Full access to owner and group, read-only for others.

- **Securing SSH keys:** 
  ```bash
  chmod 400 ~/.ssh/id_rsa
  ```
  Read-only for owner, no access for group or others.

- **Setting up web server directories:**
  ```bash
  chown -R www-data:www-data /var/www/html
  chmod -R 755 /var/www/html
  ```
  Appropriate permissions for web server files.

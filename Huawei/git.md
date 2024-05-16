### 配置用户名
git config --global user.name "Jasper Yang"  
### 配置邮箱
git config --global user.email geekhall.cn@gmail.com  
### 保存账号密码
git config --global credential.helper store  
### 查看配置
git config --global --list  
### 创建仓库
#### 方式一：git init
mkdir learn-git  
cd learn-git  
git init my-repo 
#### 方式二：git clone 
### git区域
工作区（Working Directory）：.git所在目录  
暂存区（Staging Area）：.git/index  
本地仓（Local Repository）：.git/objects  
#### 将工作区的文件添加到暂存区  
git add .
#### 将暂存区的文件提交到本地仓  
git commit -m "update"  
#### 查看提交记录
git log --oneline
### HTTPS与SSH
#### HTTPS需要验证用户名和密码  
#### SSH需要添加SSH公钥配置
ssh-keygen -t rsa -b 4096   
### 将本地仓与远程仓关联起来  
#### 方法一 本地创建仓库
git init  
git commit -m "first commit"  
git branch -M main  
git remote add origin https://github.com/test.git  
git push (-u origin main:main)   
git pull (-u origin main:main)   
#### 方法二 本地已有仓库
git remote add origin https://github.com/test.git  
git branch -M main  
git push (-u origin main:main)  
git pull (-u origin main:main)  
#### 查看远程仓库
git remote -v   
###  
在 Git 中，HEAD 是一个引用（reference），指向当前仓库中的最近一次提交（commit），通常代表当前工作的版本。它是一个指针，用于标识当前工作分支的最新状态。在执行诸如提交、合并、分支切换等操作时，HEAD 的指向会相应改变。

HEAD 通常有两种模式：

Attached HEAD：在这种模式下，HEAD 直接指向某个分支的最新提交。当你检出（checkout）一个分支时，HEAD 便附着在这个分支上。
Detached HEAD：在这种模式下，HEAD 直接指向一个具体的提交，而不是分支的最新提交。这通常发生在你检出一个特定的提交而不是分支时。

Git 是一个分布式版本控制系统，广泛应用于源代码管理。Git 的内部存储机制基于几种核心概念：对象、树、提交（commits）、以及它们之间的关系。了解这些概念有助于深入理解 Git 的工作原理。

### 1. Git 对象
Git 使用文件系统的形式存储内容，每个文件都被视为一个对象。主要有三种类型的对象：
- **Blob**（二进制大对象）：Blob 对象存储文件数据，但不包含文件名或其他元数据。
- **Tree**：Tree 对象相当于文件系统中的目录，它可以指向一组 blob 和/或其它 tree。每个 tree 对象都包含了一系列指向 blob 或其他 tree 的指针及其对应的路径名、模式（如文件权限）。
- **Commit**：Commit 对象包含一个指向 tree 对象的指针（代表项目在特定时间点的快照）、该次提交的元数据（包括作者、提交者、提交信息和指向父提交对象的指针等）。

### 2. Git 树（Tree）
Git 的树结构用于表示项目的目录结构。在 Git 中，每次提交都会存储一个树对象，该树对象记录了提交时项目目录的结构。树对象可以链接到其他树对象（表示子目录）或 blob 对象（表示文件）。通过这种方式，Git 能够高效地管理和存储项目的目录结构和文件内容。

### 3. Git 提交（Commit）
提交是 Git 的核心概念之一，每个提交对象指向一个顶层树对象（代表源代码的整个目录结构）。提交对象包含了如下信息：
- **树指针**：指向与该提交相关联的树对象。
- **父提交**：指向前一个提交，这是版本历史的关键。首次提交（初始提交）没有父提交。
- **作者和提交者信息**：包括姓名、邮箱和时间戳。
- **提交信息**：描述提交更改的信息。

### 4. 工作原理
当你在 Git 中进行提交时，发生了以下几步：
- **文件存储为 Blob**：每个新文件都被压缩并存储为一个 blob 对象。
- **目录结构存储为 Tree**：目录和文件结构被构建成一个或多个树对象。每个树对象包含指向 blob 对象或子树对象的指针。
- **创建 Commit**：创建一个提交对象，包含指向顶层树对象、父提交、作者/提交者信息和提交信息的指针。
- **更新 HEAD**：HEAD 指针更新为指向最新的提交。

### 5. SHA-1 散列
Git 使用 SHA-1 散列函数为每个对象生成一个 40 位的散列值作为其唯一标识。这意味着每个对象（blob、tree、commit）都可以通过其 SHA-1 散列值进行引用。

通过这种方式，Git 能够高效地跟踪和管理项目历史，并允许多个开发者在同一个项目上协作，而不会互相覆盖对方的工作。这些机制的设计也使得 Git 在处理大型项目时表现出卓越的性能。
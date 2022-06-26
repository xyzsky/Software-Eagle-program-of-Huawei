

# 1 版本控制的起源



##  1.1 diff 与 patch

`diff`: **用来比较两个文件或者目录之间的差异**

`patch`: **patch 是 diff 的反向操作**



## 1.2 RCS：最早的本地版本控制工具

Revsion Controller System



## 1.3 CVS & SVN： 集中式版本控制工具



​        `CVS(Concurrent Versions System)`诞生于1985年，是有史以来第一个被大规模使用的版本控制工具，**但是**其**不支持原子化提交**，会**导致客户端向服务端提交了不完整的数据**，还有**网络传输效率低**等问题。

​		

​		`SVN(Subversion)`目的是创建一个更好用的版本控制系统以取代CVS。优化了服务器上内容的存储，实现了原子提交等。但是，在**局域网外使用SVN**会存在**查看日志，提交数据等操作的延迟**。



​		**集中式版本控制存在的问题：**

- 狭窄的提交通道
  - 提交排队，不能同时修改。提交缺乏质量控制
  - 缺乏代码门禁，在本地代码提交到服务器之间缺乏检查防护
- 数据安全性差
  - 单点故障
  - 黑客攻击



## 1.4 Git



**起源：**

- 2005年4月3日，开始开发git
- 2005年4与6日，项目发布
- 2005年4与7日，Git可以作为自身的版本控制工具
- 2005年4月18日，发生第一个多分支合并
- 2005年6月16日，Linux核心2.6.12发布，Git开始维护Linux核心的源代码



**集中式 分布式版本控制系统异同：**

- 记录差异还是记录快照
  - 大部分系统以文件变更的列表的方式储存信息，这类（CSV, SVN,Perforce等）将保存的信息看做是一组基本文件和每个文件随时间逐步累积的差异
  - Git更像是将数据看做是对小型文件系统的一组快照，每次提交或者更新，它主要对当时的全部文件制作一个快照并保存这个快照的索引。**Git对待数据更像是一个快照流。**
- 中央库/分布库
  - 脆弱的中央库
    - 备份重要：集中式CVS存在单点故障，备份及其重要
    - 服务器压力大：基本上所有操作需要与服务器进行交互
    - 安全性：单点故障、黑客攻击等
    - 不适合开源项目：强调集中管理，适合人数不多的项目
  - 强壮的分布库
    - 全是服务器：数据安全，无带宽和性能瓶颈
    - 提交为本地操作：快，离线操作，编码不会被打断
    - 数据完整性：Git数据、提交全部使用SHA1哈希，以保证完整性
    - 工作模型适合分布式开发，强调个体



**SVN不适用领域：**

- 跨地域的协同开发
- 对代码的高质量追求和代码门禁

**Git不适合的领域：**

- 不适合Word等二进制文档的版本控制：Git无锁定/解锁模式，故不能排他式修改
- 整体的读授权，不能将读授权精细到目录级别（解决方案：版本库按照目录进行拆分）



**总结：**

1. Git是一个开源的、分布式的版本控制工具
2. 极快的速度
3. 简单的设计
4. 对非线性开发模式的强力支持
5. 完全分布式
6. 高效的管理能力（速度的数据量）



1. **版本控制工具的发展历史经过：**原始人工维护状态，本地RCS，集中式如VCS、SVN和分布式如Git。

2. 版本控制工具**提供了协作开发的能力**，借助它们我们可以回到任何时间的代码状态。

3. 集中式版本控制工具，几乎所有的动作**都需要服务器参与**，并且**数据安全性与服务器关系很大**。

4. **Git** **是分布式版本控制工具**，除了与服务器之前进行按需同步之外，**所有的提交操作都不需要服务器**。







# 2 Git安装与配置



## 2.1 Linux下安装Git



**包管理器方式安装：**

ubuntu 下

1. `sudo apt-get install git`
2. `sudo apt-get install git-doc git-svn git-email gitk`



源码安装：

`https://github.com/git/git/blob/master/INSTALL`



## 2.2 Windows下安装Git



`https://registry.npmmirror.com/binary.html?path=git-for-windows/`



## 2.3 Git 基本配置



**系统配置** 

`git config --system core.autocrlf`

**用户配置**

`git config --global user.name`

**仓库配置**

`git config --local remote.origin.url`



> 使用 `git config --system(global 、 local)` 可查看分别对应的配置



**配置个人身份**

`git config --global user.name "xyz"`

`git config --global user.email "904629516@qq.com"`

**文本换行符配置**

`git config --global core.autocrlf true`

`git config --global core.autocrlf input`

`git config --global core.autocrlf true`

> git 在提交时会自动把行结束符CRLF转换为LF，而在签出代码时把LF转换成CRLF。可以用core.autocrlf来设置此项功能，在Windows系统中，设置为true，签出代码时，LF会被转换为CRLF；在Linux或Mac系统中，默认换行为LF，设置为 input，默认提交时把CRLF转换为LF，签出时不转换；设置false，可以取消此功能，默认为CRLF，适用于仅在Windows系统上开发。



**文本编码配置**

`i18n.commitEncoding` 选项：用来让 `git commit log` 存储时，采用的编码，默认为`UTF-8`

`i18n.logOutputEncoding` 选项：查看 `git log`时，显示采用的编码，默认为`UTF-8`

显示路径中的中文

`git config --global core.quotepath false`



**与服务器的认证配置**

- `http / https` 协议认证

  设置口令缓存：`git config --global credential.helper store`

  添加`HTTPS`证书认证：`git config http.sslverify false`

- `ssh` 协议认证

  `SSH` 协议是一种常用的`Git`仓库访问协议，使用公钥认证、无需输入密码，加密传输，操作便利又可以保证安全性



`ssh` 认证配置过程：

1. 生成公钥

   `ssh-keygen -t -rsa -C 904629516@qq.com`

2. 添加公钥到代码平台：

   1. 登录代码平台
   2. 进入 “Profile Settings”
   3. 点击 “SSH keys”
   4. 将公钥文件中的内容复制到 “Public Key”中保存



# 3 Git 基本命令



## 3.1 Git 版本控制下的工程区域及文件状态



**Git 版本控制下的工程区域：**

1. 版本库（Repository）

   在工作区中有一个隐藏目录 `.git` ，这个文件夹就是 `Git` 的版本库，里面存放了 `Git` 用来管理该工程的所有版本数据，也可以叫做本地仓库

2. 工作区 (Working Directory)

   日常工作的代码文件或者文档所在的文件夹

3. 暂存区(stage)

   一般存放在工程根目录 `.git/index` 文件中，所有我们也可以把暂存区叫做索引 `(index)`



**Git 版本控制下的文件状态：**

1. 已提交 ( committed )

   该文件已经被安全的保存在本地数据库中

2. 已修改 ( modified )

   修改了某个文件，但还没有提交保存

3. 已暂存 ( staged )

   把已修改的文件放在下次提交时要保存的清单中



## 3.2 Git 常用命令



**工程准备**

新建工程：`git init  xx`



工程克隆：`git clone`

> 如果对二进制文件进行了区别管理，需要使用 `git lfs clone` 才能保证下载工程内容完整

**查看工作区**

查看修改内容： `git diff`

查看文件状态：`git status`

**文件修改后提交推送**

新增/删除/移动文件到暂存区(git 跟踪)：`git add / git rm / git mv`

提交更改的文件：`git commit `

推送到远端仓库：`git push`

**查看日志**

查看当前分支：`git log`

**分支管理**

列出本地分支： `git branch`

新建分支： `git branch / git checkout -b`

删除分支：`git branch -d`

切换分支：`git checkout`

更新分支：`git pull`

合并分支：`git merge`

**撤销操作**

强制回退到历史节点： `git reset`

回退本地所有修改而未提交的： `git checkout`

**分支合并**

合并目标分支内容到当前分支：`git merge / git rebase`



## 3.3 查看工作区

`git diff` 可以用于比较项目中任意两个版本（分支）的差异，也可以用来比较当前的索引和上次提交间的差异。

比较两个节点的差异： `git diff 443fdsx f332dd`

比较两个分支的差异：`git diff master`

比较当前索引和上次提交间的差异： `git diff --cached`

在 `diff` 后面加 `--name-status` 参数，**只看文件列表**:  `git diff master --name-status`



`git status` 命令用于显示工作目录和暂存区的状态



`git commit ` 主要是将暂存区的文件改动提交到本地的版本库

一次性提交所用暂存区改动的文件到版本库： `git commit -am "commit message"`



## 3.4 查看日志



`git log` 用于查看提交历史



## 3.5 推送远端仓库



`git push` 将本地的版本库的分支推送到远程服务器上对应的分支

常用的推送命令格式：`git push origin branch_name`

本地分支名可以与推送到远端的分支名不同： `git push origin branch_name:new_branch_name`





## 3.6 分支管理



**`git branch` 命令可以查看本地工程所有 `git`  分支名称**

查看远端分支： `git branch -r`

查看所有分支： `git branch -a`



`git branch ` 和 `git checkout ` 的异同：

- 相同点
  - `git branch ` 和 `git checkout -b` 都可以用于新建分支
- 区别
  - `git branch` 新建分支后并不会切换到新分支
  - `git checkout -b` 新建分支后会自动切换到新分支



删除分支： `git branch -d `  或 `git branch -D` 大写表示强制删除

删除远程分支：

1. `git branch -d -r branch_name`, 其中 `branch_name` 为本地分支名
2. `git push origin : branch_name`, 删除后推送到服务器才可以成功删除



**切换分支： `git checkout -f`  `-f` 表示强制切换**



**`git pull` 从远端服务器获取某个分支的更新，再与本地指定的分支进行自动合并**

常用的拉取分支命令： `git pull origin remote_branch:local_branch`

如果远程指定分支与本地指定分支相同： `git pull origin remote_branch`



**`git fetch` 从远端服务器中获取某个分支的更新到本地仓库**

> 与 `git pull` 不同的是， `git fetch` 在获取到更新后，并不会自动进行合并操作，这样能够留给用户一个操作空间，确认 `git fetch` 内容符合预期后，在决定是否手动合并节点

常用的获取远端分支更新命令： `git fetch origin remote_branch:local_branch`

如果远程指定分支与本地指定分支相同： `git fetch origin remote_branch`



## 3.7 分支合并



`git merge` 用于从指定分支（节点）合并到当前分支的操作

常用的合并分支命令： `git merge branch_name`



`git rebase` 合并目标分支内容到当前分支



区别：

`git merge` 的优势是它保留了分支的结构与历史提交目录，但同时也导致了过多复杂化的提交历史

- 记录下合并动作，很多时候这种合并动作是垃圾信息

- 不会修改原 `commit ID`

- 冲突只解决一次

- 分支看着不大整洁，但是能看出合并的先后顺序

- 记录了真实的 `commit` 情况，包括每个分支的详情



`git rebase` 

- 改变当前分支 `branch out` 的位置

- 得到更简洁的项目历史

- 每个 `commit` 都需要解决冲突

- 修改所有 `commit ID`



> 详细阅读： https://zhuanlan.zhihu.com/p/57872388



## 3.8 撤销操作



`git reset` 用于撤销当前工作区中的某些 `git add/commit ` 操作，可以将工作区内容回退到历史提交节点。



用于回退本地所有修改而没有提交的文件内容： `git checkout .`  (谨慎使用) ， 可以用 `git checkout -filename `

将工作区回退到某个提交版本： `git checkout commit_id`




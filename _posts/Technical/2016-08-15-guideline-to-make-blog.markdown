---
layout: post
title:  "Create a github blog"
date:   2016-08-15
categories: Technical
tags: Jekyll Blog
---

### Summary
This article provides two methods to create a github page/blog (github.io). All the procedures are based on Ubuntu.

*Prerequisite:*

+ A Github account
+ git is installed (`sudo apt-get git`)

___

### Table of Content

1. [Lazy way](#Lazy way) (fork and modify an existing blog)
2. [Hard way](#Hard way) (create from scratch) [To be edited]

___

### Part 1. Lazy way<a name="Lazy way"></a>

#### 1.1. Fork, clone and modify

![fork.png]({{site.url}}/public/post_resource/Technical/Create_a_github_blog/fork.png)

1. Fork a repository template from others
2. Click "Settings"
3. Rename the repository to "*yourUserName.github.io*" (yourUserName should be in lower case)

After forking a repository, clone the repository to your local machine.

	git clone https://github.com/Huangying-Zhan/huangying-zhan.github.io.git

Open *_config.yml* and make modifications according to your needs. The following parts are required to update.

+ Blogger's information
+ Website's inforamtion

Other parts can be updated if necessary.

<br><br>

#### 1.2. Delete, add and upload

How to write your own posts and update the website? First of all, you need to clean up the existing posts first. There is a folder named *_post*, which stores all posts that you are going to create. Clear the whole folder except keeping one post. This kept post is a reference for you for writing your own article later on.

Suppose you have written a new post. Now we are going to update the changes we have made so far and upload the repository to Github.

```
cd $BLOG # $BLOG is the directory of the blog on your local machine
git add . # track all modified files
git commit -m "First update" # Submit all modified files with message "First update"
git push origin master # Upload the submitted files to Github
```

Wait for a while and refresh your website. You should see a brand new page with your first post. 

~ The blog is created! ~

___

### Part 2. Hard way <a name="Hard way"></a>

To be edited.
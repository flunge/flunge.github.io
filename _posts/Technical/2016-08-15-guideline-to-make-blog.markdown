---
layout: post
title:  "Create a github blog"
date:   2016-08-15
categories: Technical
tags: Jekyll Blog
---

### Summary
This article provides two ways to create a github page/blog (github.io). All the procedures are based on Ubuntu.

*Prerequisite:*

+ A Github account
+ git is installed (`sudo apt-get git`)







**Table of Content**

1. Lazy way (fork and modify an existing blog)
2. Hard way (create from scratch)


### Part 1. Lazy method


#### 1.1. Fork, clone and modify

![fork.png]({{site.url}}/public/post_resource/Technical/Create_a_github_blog/fork.png)

1. Fork a repository template from others
2. Click "Settings"
3. Rename the repository to "*yourUserName.github.io*" (yourUserName should be in lower case)
4. Update *_config.yml* and others if necessary

After forking a repository, clone the repository to your local machine.

	git clone https://github.com/Huangying-Zhan/huangying-zhan.github.io.git

Open *_config.yml* and make modifications according to your need. Some necessary parts requiring update are,

+ Blogger's information
+ Website's inforamtion

Other parts can be updated if necessary.

___

#### 1.2. Delete, add and upload

How to write your own posts and update the website? First, you need to clean up the existing posts first. There is a folder named



```
git add .
git commit -m "update _config.yml"
git push origin master
```


## Create .github.io
Suppose you have a github account.

1. Click New repository
2. Repository name must be username.github.io e.g. huangying-zhan.github.io
3. Click Settings and the button "Launch automatic page generator"
4. Choose a theme
5. A simple github.io is created

## Install necessary package
```
$ sudo apt-get install git
$ sudo apt-get install ruby-full
$ sudo apt-get install gem
    
$ sudo gem install jekyll
$ sudo gem install bundler
$ sudo gem install jekyll --pre
$ bundler install
```

___
*For ruby version < 2.0, ruby2.3.1 is installed as following.*

Install or update necessary packages

```
$ sudo apt-get -y update
$ sudo apt-get install cmake
$ sudo apt-get install -y build-essential zlib1g-dev libyaml-dev libssl-dev libgdbm-dev libreadline-dev
   libncurses5-dev libffi-dev curl git-core openssh-server redis-server postfix checkinstall libxml2-dev 
  libxslt-dev libcurl4-openssl-dev libicu-dev mysql-client libmysqlclient-dev libreadline6-dev  
```

Download and install ruby

```
$ mkdir /tmp/ruby
$ cd /tmp/ruby
$ curl --progress https://cache.ruby-lang.org/pub/ruby/2.3/ruby-2.3.1.tar.gz | tar xz
$ cd ruby-2.3.1
$ ./configure
$ make
$ sudo make install
```
___


## Basic operation of github.io

In the following steps, huangying-zhan.github.io will be used as an example. 
"Huangying-Zhan" should be changed to your username if necessary.

#### 1. Download/Clone Huangying-Zhan.github.io
    
    $ git clone "https://github.com/Huangying-Zhan/huangying-zhan.github.io"
        
#### 2. Add remote address

    $ git remote add origin https://github.com/Huangying-Zhan/huangying-zhan.github.io.git

After adding the remote address, we can check by using command:
        
    $ git remote -v
        
#### 3. add->commit->push
         
    $ git add
    $ git commit
    $ git push -u origin master


## Usage of Jekell

Suppose you have cloned your repository to a local directory

Change directory to your directory

`$ cd huangying-zhan.github.io.git`

Create a new blog

`$ jekyll new blog`
`$ cd blog`

Create a server at localhost: https://localhost:4000

`$ bundle exec jekyll serve`






### Push to Github without password

Refer to the following link.
[Generating ssh-key](https://help.github.com/articles/generating-an-ssh-key/)



### Reference

* [ytysj.githu.io](http://ytysj.github.io/blog/myblog3)

* [Blog of 只缘心高嫌地窄](http://blog.csdn.net/u014015972/article/details/50497254)

* [Jekyll Documentation](https://jekyllrb.com/docs/home/)

* [Update ruby](http://my.oschina.net/fxhover/blog/382634)
1
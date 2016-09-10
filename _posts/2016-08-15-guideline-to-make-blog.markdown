---
layout: post
title:  "Guideline to make blog!"
date:   2016-08-15
categories: General
tags: Jekyll
---

Procedures to start a github.io
====================

## Create .github.io
Suppose you have a github account.

1. Click New repository
2. Repository name must be username.github.io
> e.g. huangying-zhan.github.io
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



### Lazy method

1. Fork a repository template from others
2. Change name of repository to "username.github.io"
3. Clone to local
4. Update _config.yml and others if necessary

After forking a repository

`git clone https://github.com/Huangying-Zhan/huangying-zhan.github.io.git`

After updating _config.yml

```
git add .
git commit -m "update _config.yml"
git push origin master
```



### Push to Github without password

Refer to the following link.
[Generating ssh-key](https://help.github.com/articles/generating-an-ssh-key/)

    
    

### Reference

* [ytysj.githu.io](http://ytysj.github.io/blog/myblog3)

* [Blog of 只缘心高嫌地窄](http://blog.csdn.net/u014015972/article/details/50497254)

* [Jekyll Documentation](https://jekyllrb.com/docs/home/)

* [Update ruby](http://my.oschina.net/fxhover/blog/382634)

[Network Time Foundation](https://www.nwtime.org/) is converting the official NTP documentation websites to Hugo and Markdown. Anyone can download the documentation source and generate their own HTML copy of the documentation. Users with a github account can also edit the documentation and generate git pull requests for their edits to be reviewed. This README contains instructions for getting the NTP documentation source, generating a copy of the
documentation, and issuing a git pull request.

## Requirements

In order to render the Markdown into HTML using Hugo (recommended), the following software needs to be installed:

* [Hugo (Extended version)](https://github.com/gohugoio/hugo/releases)
* [Node.js](https://nodejs.org/en/download/)

Add the following Node packages:

```
npm install -D autoprefixer
npm install -D postcss-cli
npm install -D postcss
```

Grab the [ntpdoc repository](https://github.com/nwtime/ntpdoc/):

```
git clone https://github.com/nwtime/ntpdoc

```

## Building the Documentation

Once you've installed the requirements, start Hugo from the `ntpdoc` directory:

```
hugo server
```

This message indicates success and you can view the ntpdoc website by opening the specified URL in a web browser:

```
Web Server is available at //localhost:1313/ (bind address 127.0.0.1)
Press Ctrl+C to stop
```

If you instead get an error similar to this:

```
Error: Error building site: TOCSS: failed to transform "scss/main.scss" (text/x-scss): resource "scss/scss/main.scss_9fadf33d895a46083cdd64396b57ef68" not found in file cache
```

you have not installed the extended version of Hugo.

## Editing the Documentation

If Hugo is running as you save edits to an ntpdoc file, it should automatically display the changes--occasionally you will need to refresh your browser to see the changes.

To issue a git pull request for your edits, use the instructions at
https://help.github.com/articles/using-pull-requests.
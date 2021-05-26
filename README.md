The [Network Time Foundation](https://www.nwtime.org/) is converting the official NTP documentation websites to Hugo and Markdown. Anyone can download the documentation source and generate their own HTML copy of the documentation. Users with a github account can also edit the documentation and generate git pull requests for their edits to be reviewed. This README contains instructions for getting the NTP documentation source, generating a copy of the
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
git clone https://github.com/nwtime/ntpdoc ntpdoc
cd ntpdoc
mkdir themes
cd themes
```

Finally, add the [Docsy theme](https://github.com/google/docsy) while in the `ntpdoc/themes` directory:

```
git clone https://github.com/google/docsy 
cd docsy
git submodule update --init --recursive
```

## Building the Documentation

Once you've installed the requirements, `cd` back to `ntpdoc` and start Hugo:

```
hugo server
```

This message indicates success and you can view the ntpdoc website by opening the specified URL in a web browser:

```
Web Server is available at //localhost:1313/ (bind address 127.0.0.1)
Press Ctrl+C to stop
```

If you instead get this error:

```
Error: Error building site: TOCSS: failed to transform "scss/main.scss" (text/x-scss): resource "scss/scss/main.scss_9fadf33d895a46083cdd64396b57ef68" not found in file cache
```

you have not installed the extended version of Hugo, which is required by the Docsy theme.

## Editing the Documentation

If Hugo is running as you save edits to an ntpdoc file, it should automatically display the changes--occasionally you will need to refresh your browser to see the changes.

To issue a git pull request for your edits, use [these instructions](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).
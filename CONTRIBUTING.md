# Contributing to Orca One
We love your input! We want to make contributing to this project as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

## We Develop with Github
We use github to host code, to track issues and feature requests, as well as accept pull requests.

## We Use [Github Flow](https://docs.github.com/en/get-started/quickstart/github-flow), So All Code Changes Happen Through Pull Requests
Pull requests are the best way to propose changes to the codebase (we use [Github Flow](https://docs.github.com/en/get-started/quickstart/github-flow)). We actively welcome your pull requests:

1. Fork the repo and create your branch from `develop`.
2. Issue that pull request to `develop`!

## Configuring the Project
### Requirements
1. [Visual Studio Code](https://code.visualstudio.com/download)
2. [PlatformIO IDE (Extension)](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
### Build
1. Go to `PlatformIO` tab on your `Visual Studio Code`
2. In `Project Tasks` open a board to build and burn (e.g. `m5stack-cardputer`)
3. In `Platform` click on `Build Filesystem Image` and after in `Upload Filesystem Image`
4. In `General` click on `Build` and after in `Upload`
5. Done! The project will be compiled and burned on the chosen device.
### Selecting default board 

    Please do not commit `platformio.ini` if you only change `default_envs`

1. Open `platformio.ini` file and go to session `[platformio]`
2. Adjust first line of `default_envs` to your prefered board:
```ini
[platformio]
default_envs = 
	m5stack-cardputer
	m5stack-cplus1_1
	m5stack-cplus2
```

## Any contributions you make will be under the MIT Software License
In short, when you submit code changes, your submissions are understood to be under the same [MIT License](http://choosealicense.com/licenses/mit/) that covers the project. Feel free to contact the maintainers if that's a concern.

## Report bugs using Github's [issues](https://github.com/cyberjulio/orca-one/issues)
We use GitHub issues to track public bugs. Report a bug by [opening a new issue](); it's that easy!

**Great Bug Reports** tend to have:

- A quick summary and/or background
- Steps to reproduce
- What you expected would happen
- What actually happens
- Notes (possibly including why you think this might be happening, or stuff you tried that didn't work)

People *love* thorough bug reports. I'm not even kidding.

## License
By contributing, you agree that your contributions will be licensed under its MIT License.

## References
This document was adapted from the open-source contribution guidelines for [Facebook's Draft](https://github.com/facebookarchive/draft-js/blob/main/CONTRIBUTING.md)
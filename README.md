# hayashi

:seedling: a tiny distro-independent package manager in C++.

## Usage

### Pkg Config

A pkg is defined in an ini file at one of the [collections](#collections) in `~/.hayashi/pkg/`.

```ini
[pkg]
name=pkg_name
url=git_url
bash=install_script
```

> white space is ignored

### Installing a pkg

Install pkg defined in `~/.hayashi/pkg/`:

    $ hayashi add pkg_name

> This will search for a [pkg config](#pkg-config), clone the git repo and run the install script.

### Adding a pkg config

Add a pkg config at `~/.hayashi/pkg/custom/pkg_name.ini`:

    $ hayashi pkg add pkg_name

You can also specify a git url for the pkg:

    $ hayashi pkg add pkg_name git_url

### Showing info about a pkg

	$ hayashi show pkg_name

## Installation

### Building from source

	$ cd ~/
    $ git clone --depth 1 https://github.com/CrispyBaccoon/hayashi.git
    $ make && sudo make install
    $ make config

## Configured packages

### Collections

Packages are stored in collections. Hayashi includes some base packages in the core collection.

### Core packages

There are multiple packages included in the repo.
- [cbonsai](https://gitlab.com/jallbrit/cbonsai). a bonsai tree generator written in C.
- [neovim](https://github.com/neovim/neovim). Vim-fork focused on extensibility and usability.
- [fzf](https://github.com/junegunn/fzf). a general-purpose command-line fuzzy finder.
- [bat](https://github.com/sharkdp/bat). A cat(1) clone with wings.
- [ohmyzsh](https://github.com/ohmyzsh/ohmyzsh). A delightful framework for managing your zsh configuration.
- [vim-plug](https://github.com/junegunn/vim-plug). A minimalist Vim plugin manager.


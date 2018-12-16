# Theming guide

## General concepts
First, there are some important concepts that are needed to understand how theming in Nwsh works. The themes are composed of:
* Format: how the information is shown on the screen (username, hostname, current directory...)
* Colors: the colors that are used for each of the elements of the format

Format and colors are totally independent, so choosing a determinate format does not influence the colors available to theme it.

## Formats
There are several formats to choose from in Nwsh, which are indentified by numbers.
### Format 0:
`username@hostname directory >`

Being:

0. Username
1. '@'
2. Hostname
3. Directory
4. '>'

### Format 1:
`>`

Being:

0. '>'

### Format 2:
`username at hostname directory >`

Being:

0. Username
1. at
2. Hostname
3. Directory
4. '>'

In this case the directory will only show as the name of the last directory in pwd. For example if the current diretory is /home/user/Docs, the directory will appear as Docs. This is to maintain a cleaner style, with less information, but still maintaining a reference to the current directory.

## Colors
There are 16 colors available in Nwsh, also identified by numbers:
 * 0: Black
 * 1: Red
 * 2: Green
 * 3: Yellow
 * 4: Blue
 * 5: Magenta
 * 6: Cyan
 * 7: Light Gray
 * 8: Dark Gray
 * 9: Light Red
 * 10: Light Green
 * 11: Light Yellow
 * 12: Light Blue
 * 13: Light Magenta
 * 14: Light Cyan
 * 15: White

## How can I customize my prompt?
In order to customize it you will have to edit the file located in ~/.nwshrc. There you can choose one format from the ones above using:

`theme numOfFormat`

or

`:t numOfFormat`

You can then choose the colors of each one of the element that compose the format by using:

`color numOfElement numOfColor`

or

`:c numOfElement numOfColor`

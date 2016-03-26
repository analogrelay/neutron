# CEF folder

You need to download a distribution of CEF from https://cefbuilds.com/ and place it here. Unpack the `7z` file to one of the following folders depending on OS/Architecture:

* Windows x64: `win-x64`
    * Example command line (from root of repo):
        * `7z x -ovendor\cef\win-x64\ "C:\Path\To\cef_binary_3.2556.1368.g535c4fb_windows64.7z"`
        * Then move the contents of the `vendor\cef\win-x64\cef_...` folder up one level.
        * `vendor\cef\win-x64\cefclient` should exist, along with the other CEF folders (as peers).
* Other: TBD

# SVG Export to Mobile Resource
Tool to export svg files to mobile assets

<img src="https://github.com/CamiloDelReal/svg-export-to-mobile-resources/blob/develop/img/app/logo.svg" />

## This project will not be maintenance anymore
I am not working for Qt since a while and updates started to become hard after so much changes in Qt 6

### Features
- Multiples export templates
  * Name configurations
    - Wrapper directory
    - Resource file
  * Size configurations
- Custom file name for resources, based on key words
  * Key words must be inside brackets: [KEYWORDS]
  * Allowed key words: DIRECTORYPREFIX, LABEL, WIDTH, HEIGHT, SCALE, RESOURCENAME
    - DIRECTORYPREFIX: String prefix for a wrapper directory when export a resource
    - LABEL: String value id for the size template
    - WIDTH: Width value of the size template
    - HEIGHT: Height value of the size template
    - SCALE: Scale value of the size template
    - RESOURCENAME: String value id for the exported resource

### Future Features
- Allow to create new templates (UI is missing, the core is ready)
- Installer

### Default Templates
- Android Icon Launcher
  * Allows export to: ldpi, mdpi, hdpi, xhdpi, xxhdpi, xxxhdpi, web

### Future Default Templates
- iOS App icon

### Libraries
- Qt Framework Open Source
  * [Qt Framework](https://www.qt.io/)
- Icons
  * [Material Design Icons](https://materialdesignicons.com)
- Colors
  * [Material Design Colors](https://material.io/resources/color/)
- Libraries
  * [XMaterialControls](https://github.com/CamiloDelReal/x_material_controls)
  * [XOrm](https://github.com/CamiloDelReal/x_orm)

### Screenshots
<p float="left">
<img src="https://github.com/CamiloDelReal/svg-export-to-mobile-resources/blob/develop/screenshots/export-view-1.png" width="50%" height="50%" />
<img src="https://github.com/CamiloDelReal/svg-export-to-mobile-resources/blob/develop/screenshots/settings-view-1.png" width="50%" height="50%" />
</p>

# SVG Export to Mobile Resource
Tool to export svg files to mobile assets

<img src="https://github.com/CamiloDelReal/project-weather-x/blob/develop/artwork/icons/logo.png" />

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
- Allow create new templates (UI is missing, the core is ready)

### Default Templates
- Android Icon Launcher
  * Allow export to: ldpi, mdpi, hdpi, xhdpi, xxhdpi, xxxhdpi, web

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
  * [X Material Controls](https://github.com/CamiloDelReal/x_material_controls)
  * [X Orm](https://github.com/CamiloDelReal/x_orm)

### Screenshots
<p float="left">
<img src="https://github.com/CamiloDelReal/svg-export-to-mobile-resources/blob/develop/screenshots/export-view-1.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/svg-export-to-mobile-resources/blob/develop/screenshots/settings-view-1.png" width="30%" height="30%" />
</p>

## [TODO] Dependencies

- the gnu avr toolchain
- python 3
  - pyyaml `sudo pip install pyyaml`
  - markdown `sudo pip install markdown`


## Coding Conventions

### Comments
`/** ... */` comments are to be written in YAML, so they can be processed by
external tools to generate documentation, and for other purposes.

* When read the following will be stripped:
    * The first line (typically `/**`)
    * The last line (typically ` */`)
    * The first two characters of each line (typically ` *`)

* All elements are optional.
* All list elements are repeatable.
* All of these elements may all be specified from within any scanned file.
* Some of these elements have defaults (commented below); giving them a value
  explicitly will override that.
* The element `.ignore` may appear in any list, and should be ignored.


        - &atom '<boolean>|<number>|<string.markdown>'

        - &value-map
          type: *atom
          name: *atom
          description: *atom
          values: [ *value-map ]
          notes: [ *atom ]


        - &description-map
          # the file description
          description: *atom

        - &function-map
          function:
            << : *value-map
            arguments: *value-map
            return value: *value-map

        - &macro-map
          macro: { << : *value-map }

        - &typedef-map
          typedef: { << : *value-map }


        - &file-map
          file:
            # name: taken from the filesystem
            # description: taken from the '[filename].md' if it exists
            << : [ *description-map, *value-map ]
            functions: [ *function-map ]
            macros: [ *macro-map ]
            typedefs: [ *typedef-map ]

        - &directory-map
          directory:
            # name: taken from filesystem
            # description: taken from the 'readme.md' if it exists
            << : *value-map
            files: [ *file-map ]
            directories: [ *directory-map ]

        - &project-map
          project:
            << : *value-map
            directories: [ *directory-map ]

        - projects: [ *project-map ]


-------------------------------------------------------------------------------

Copyright &copy; 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (see "doc/license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>


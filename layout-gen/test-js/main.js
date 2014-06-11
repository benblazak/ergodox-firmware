// ----------------------------------------------------------------------------
// colors
// ----------------------------------------------------------------------------

/*
 * Notes:
 * - From <http://ethanschoonover.com/solarized>
 *
 * Usage:
 * ```
 *         light                        dark
 *         ---------------------------  ---------------------------
 * base03  ...........................  background ................
 * base02  ...........................  background highlights .....
 * base01  optional emphasized content  comments ..................
 * base00  body text .................  ...........................
 * base0   ...........................  body text .................
 * base1   comments ..................  optional emphasized content
 * base2   background highlights .....  ...........................
 * base3   background ................  ...........................
 * ```
 */
var solarized = {
  base03  : '#002b36',
  base02  : '#073642',
  base01  : '#586e75',
  base00  : '#657b83',
  base0   : '#839496',
  base1   : '#93a1a1',
  base2   : '#eee8d5',
  base3   : '#fdf6e3',
  yellow  : '#b58900',
  orange  : '#cb4b16',
  red     : '#dc322f',
  magenta : '#d33682',
  violet  : '#6c71c4',
  blue    : '#268bd2',
  cyan    : '#2aa198',
  green   : '#859900',
};


/*
 * Notes:
 * - Names taken from Elm:
 *   <http://library.elm-lang.org/catalog/elm-lang-Elm/0.12.3/Color>
 * - Real names from Tango:
 *   <http://tango.freedesktop.org/Tango_Icon_Theme_Guidelines>
 *   ```
 *   yellow   : butter
 *   orange   : orange
 *   brown    : chocolate
 *   green    : chameleon
 *   blue     : sky blue
 *   purple   : plum
 *   red      : scarlet red
 *   gray     : aluminum (light)
 *   charcoal : aluminum (dark) 
 *   ```
 */
var tango = {
  lightYellow   : '#fce94f', yellow   : '#edd400', darkYellow   : '#c4a000',
  lightOrange   : '#fcaf3e', orange   : '#f57900', darkOrange   : '#ce5c00',
  lightBrown    : '#e9b96e', brown    : '#c17d11', darkBrown    : '#8f5902',
  lightGreen    : '#8ae234', green    : '#73d216', darkGreen    : '#4e9a06',
  lightBlue     : '#729fcf', blue     : '#3465a4', darkBlue     : '#204a87',
  lightPurple   : '#ad7fa8', purple   : '#75507b', darkPurple   : '#5c3566',
  lightRed      : '#ef2929', red      : '#cc0000', darkRed      : '#a40000',
  lightGray     : '#eeeeec', gray     : '#d3d7cf', darkGray     : '#babdb6',
  lightCharcoal : '#888a85', charcoal : '#555753', darkCharcoal : '#2e3436',
};



// ----------------------------------------------------------------------------
// keyboards
// ----------------------------------------------------------------------------


/*
 * Usage:
 * ```
 * var keyboards = {
 *   id: {  // keyboard name
 *     size: [1,1],  // the number of 1x keys it would take to cover the board
 *     keys: {
 *       id: {  // configuration name
 *         id: {  // key name
 *           size: 1,           // 1 = 1x key, 2 = 2x key, etc.
 *           position: [0,0],   // of the top left of the key
 *           rotation: 0,       // in degrees
 *           value: 'transp',   // name of the assigned key-function
 *         },
 *         // ... more keys
 *       },
 *       // ... more configurations
 *       // - `all`: keys belong to all configurations
 *       // - [other]: keys belong to the named configuration; at least one
 *       //   other configuration must be specified; a configuration may be
 *       //   empty (then only the `all` keys are in that configuration)
 *     },
 *   },
 *   // ... more keyboards
 * };
 * ```
 */
var keyboards = {};


/*
 * Notes:
 * - From the firmware source:
 *   ```
 *   // left hand, spatial positions
 *   k50,k51,k52,k53,k54,k55,k56,      
 *   k40,k41,k42,k43,k44,k45,k46,      
 *   k30,k31,k32,k33,k34,k35,          
 *   k20,k21,k22,k23,k24,k25,k26,      
 *   k10,k11,k12,k13,k14,              
 *                           k05,k06,  
 *                       k15,k16,k04,  
 *                       k03,k02,k01,  
 *                                     
 *   // right hand, spatial positions
 *       k57,k58,k59,k5A,k5B,k5C,k5D,  
 *       k47,k48,k49,k4A,k4B,k4C,k4D,  
 *           k38,k39,k3A,k3B,k3C,k3D,  
 *       k27,k28,k29,k2A,k2B,k2C,k2D,  
 *               k19,k1A,k1B,k1C,k1D,  
 *   k07,k08,                          
 *   k09,k17,k18,                      
 *   k0C,k0B,k0A )                     
 *   ```
 */
keyboards['ErgoDox'] = {
  size: [18,8],
  keys: {
    all: {

      // left hand, roughly from upper left to bottom right

      k50: { position: [0,0], size: 1.5 },
      k51: { position: [1.5,0] },
      k52: { position: [2.5,0] },
      k53: { position: [3.5,0] },
      k54: { position: [4.5,0] },
      k55: { position: [5.5,0] },
      k56: { position: [6.5,0] },

      k40: { position: [0,1], size: 1.5 },
      k41: { position: [1.5,1] },
      k42: { position: [2.5,1] },
      k43: { position: [3.5,1] },
      k44: { position: [4.5,1] },
      k45: { position: [5.5,1] },
      k46: { position: [6.25,1.25], size: 1.5, rotation: -90 },

      k30: { position: [0,2], size: 1.5 },
      k31: { position: [1.5,2] },
      k32: { position: [2.5,2] },
      k33: { position: [3.5,2] },
      k34: { position: [4.5,2] },
      k35: { position: [5.5,2] },

      k20: { position: [0,3], size: 1.5 },
      k21: { position: [1.5,3] },
      k22: { position: [2.5,3] },
      k23: { position: [3.5,3] },
      k24: { position: [4.5,3] },
      k25: { position: [5.5,3] },
      k26: { position: [6.25,2.75], size: 1.5, rotation: -90 },

      k10: { position: [0.5,4] },
      k11: { position: [1.5,4] },
      k12: { position: [2.5,4] },
      k13: { position: [3.5,4] },
      k14: { position: [4.5,4] },

      k05: { position: [6.5,5] },
      k06: { position: [7.5,5] },

      k04: { position: [7.5,6] },

      k01: { position: [7.5,7] },

      // right hand, roughly from upper left to bottom right

      k57: { position: [10.5,0] },
      k58: { position: [11.5,0] },
      k59: { position: [12.5,0] },
      k5A: { position: [13.5,0] },
      k5B: { position: [14.5,0] },
      k5C: { position: [15.5,0] },
      k5D: { position: [16.5,0], size: 1.5 },

      k47: { position: [10.25,1.25], size: 1.5, rotation: 90 },
      k48: { position: [11.5,1] },
      k49: { position: [12.5,1] },
      k4A: { position: [13.5,1] },
      k4B: { position: [14.5,1] },
      k4C: { position: [15.5,1] },
      k4D: { position: [16.5,1], size: 1.5 },

      k38: { position: [11.5,2] },
      k39: { position: [12.5,2] },
      k3A: { position: [13.5,2] },
      k3B: { position: [14.5,2] },
      k3C: { position: [15.5,2] },
      k3D: { position: [16.5,2], size: 1.5 },

      k27: { position: [10.25,2.75], size: 1.5, rotation: 90 },
      k28: { position: [11.5,3] },
      k29: { position: [12.5,3] },
      k2A: { position: [13.5,3] },
      k2B: { position: [14.5,3] },
      k2C: { position: [15.5,3] },
      k2D: { position: [16.5,3], size: 1.5 },

      k19: { position: [12.5,4] },
      k1A: { position: [13.5,4] },
      k1B: { position: [14.5,4] },
      k1C: { position: [15.5,4] },
      k1D: { position: [16.5,4] },

      k07: { position: [9.5,5] },
      k08: { position: [10.5,5] },

      k09: { position: [9.5,6] },

      k0C: { position: [9.5,7] },
    },

    'Long Thumbs': {
      k03: { position: [5,6.5], size: 2, rotation: -90 },
      k02: { position: [6,6.5], size: 2, rotation: -90 },

      k0B: { position: [10,6.5], size: 2, rotation: 90 },
      k0A: { position: [11,6.5], size: 2, rotation: 90 },
    },

    'Split Thumbs': {
      k15: { position: [5.5,6] },
      k16: { position: [6.5,6] },

      k03: { position: [5.5,7] },
      k02: { position: [6.5,7] },

      k17: { position: [10.5,6] },
      k18: { position: [11.5,6] },

      k0B: { position: [10.5,7] },
      k0A: { position: [11.5,7] },
    },

  },
};



// ----------------------------------------------------------------------------
// test: functions and event bindings
// ----------------------------------------------------------------------------

// TODO:
// - need to actually plan the organization of the key data...
// - how shall we handle switching between different layers?

var drawKey = function(key) {
  var size     = key.size     || 1;
  var position = key.position || [0,0];
  var rotation = key.rotation || 0;

  key.raphael = {};

  key.raphael.rect =
    paper.rect( position[0]*keysize,
                position[1]*keysize,
                size*keysize,
                keysize )
         .attr({ 'fill': tango.lightBlue,
                 'stroke': tango.lightGray })
         .transform('r'+rotation);

  key.raphael.text =
    paper.text( position[0]*keysize + size*keysize/2,
                position[1]*keysize + keysize/2,
                key.value )
         .attr({ 'font-family': 'monospace' })
         .transform( 'r' + rotation +
                     's' + Math.min( size*8/key.value.length, 8/3) );

  key.raphael.button =
    paper.rect( position[0]*keysize,
                position[1]*keysize,
                size*keysize,
                keysize )
         .attr({ 'fill': '#fff',
                 'stroke': 'none',
                 'opacity': 0 })
         .transform('r'+rotation)
         .mouseover(function() {
           key.raphael.button.attr({ 'opacity': .1 });
         })
         .mouseout(function() {
           key.raphael.button.attr({ 'opacity': 0 });
         })
         .mouseup(function() {
           key.raphael.rect.attr({ 'fill': tango.lightOrange });
         });
}

var updateKey = function(key) {
  var size     = key.size || 1;
  var rotation = key.rotation || 0;

  key.raphael.text
    .attr({'text': key.value})
    .transform( 'r' + rotation +
                's' + Math.min( size*8/key.value.length, 8/3) );
}


// main() (kind of) -----------------------------------------------------------

window.onload = function() {
  // style
  document.body.style.background = tango.lightGray;

  // setup
  keyboard = keyboards['ErgoDox'];
  configuration = 'Long Thumbs';

  keysize = 990/keyboard['size'][0];

  paper = Raphael( 0, 0, keyboard.size[0]*keysize+10,
                         keyboard.size[1]*keysize+10 );

  // draw bounding box
  paper.rect( 0, 0,
              keyboard.size[0]*keysize+10,
              keyboard.size[1]*keysize+10,
              5 )
       .attr('stroke', tango.lightBlue);

  // draw keys
  for (var id in keyboard.keys[configuration]) {
    var key = keyboard.keys[configuration][id];
    key.position[0] += 5/keysize;
    key.position[1] += 5/keysize;
    key.value = id;
    drawKey(key);
  }
  for (var id in keyboard.keys.all) {
    var key = keyboard.keys['all'][id];
    key.position[0] += 5/keysize;
    key.position[1] += 5/keysize;
    key.value = id;
    drawKey(key);
  }
}


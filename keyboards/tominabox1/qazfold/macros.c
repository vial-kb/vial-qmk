/* Macros */
bool is_shift_lock_active = false; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOCK_SHIFT:
      if (record->event.pressed) {
        if (!is_shift_lock_active) {
          is_shift_lock_active = true;
          register_code(KC_LSFT);
        }
        else{
          is_shift_lock_active = false;
          unregister_code(KC_LSFT);
        }         
      } 
      break;

    case COPY:
      if (record->event.pressed) {
             SEND_STRING(SS_LCTL("c"));
        if (is_shift_lock_active) {
          is_shift_lock_active = false;
          unregister_code(KC_LSFT);
        }
      } 
      break;
    case CUT:
      if (record->event.pressed) {
             SEND_STRING(SS_LCTL("x"));
         if (is_shift_lock_active) {
          is_shift_lock_active = false;
          unregister_code(KC_LSFT);
        }
      } 
      break;
      
   case PASTE:
      if (record->event.pressed) {
             SEND_STRING(SS_LCTL("v"));
         if (is_shift_lock_active) {
          is_shift_lock_active = false;
          unregister_code(KC_LSFT);
        }
      } 
      break;
      
      case MATHFRAC:
      if (record->event.pressed) {
	SEND_STRING(SS_TAP(X_BSLS)"frac ");
      } 
      break;

      
      case MATHENVCENTER:
      if (record->event.pressed) {
	 register_code(KC_LSFT);	
         SEND_STRING(SS_LCTL("m"));
	 unregister_code(KC_LSFT);
      } 
      break;
            
    case DOMATH:
        if (record->event.pressed) {
             SEND_STRING(SS_LALT("emsa")); 
        } else {
        }
        break;
        
     case CUTWORD:
      if (record->event.pressed) {
		unregister_code(KC_LSFT);
		register_code(KC_LCTL);
        SEND_STRING(SS_TAP(X_RIGHT));
        SEND_STRING(SS_TAP(X_LEFT));
		register_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_RIGHT));
		unregister_code(KC_LSFT);
		unregister_code(KC_LCTL);		
        SEND_STRING(SS_LCTL("x"));
        is_shift_lock_active = false;
      } 
      break;      
       
     case COPYWORD:
      if (record->event.pressed) {
		unregister_code(KC_LSFT);
		register_code(KC_LCTL);
        SEND_STRING(SS_TAP(X_RIGHT));
        SEND_STRING(SS_TAP(X_LEFT));
		register_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_RIGHT));
		unregister_code(KC_LSFT);
		unregister_code(KC_LCTL);		
        SEND_STRING(SS_LCTL("c"));
        is_shift_lock_active = false;
      } 
      break;       

     case CUTLINE:
      if (record->event.pressed) {
		unregister_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_END));
        SEND_STRING(SS_TAP(X_HOME));
		register_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_END));
		unregister_code(KC_LSFT);		
        SEND_STRING(SS_LCTL("x"));
        is_shift_lock_active = false;
      } 
      break;       

     case COPYLINE:
      if (record->event.pressed) {
		unregister_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_END));
        SEND_STRING(SS_TAP(X_HOME));
		register_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_END));
        SEND_STRING(SS_TAP(X_END));
		unregister_code(KC_LSFT);		
        SEND_STRING(SS_LCTL("c"));
        is_shift_lock_active = false;
      } 
      break;       

    case LINEDOWN:
      if (record->event.pressed) {
		unregister_code(KC_LSFT);
		SEND_STRING(SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME)SS_TAP(X_HOME));  
        register_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_END));	
        unregister_code(KC_LSFT);
        SEND_STRING(SS_LCTL("c"));
        SEND_STRING(SS_TAP(X_END)SS_TAP(X_ENT));
        SEND_STRING(SS_LCTL("v"));        
        is_shift_lock_active = false;
      } 
      break;
      
    case COPYDOWN:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTL("c"));
          is_shift_lock_active = false;
          unregister_code(KC_LSFT);
          SEND_STRING(SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END)SS_TAP(X_END));	  
          SEND_STRING(SS_TAP(X_ENT));	        
	  SEND_STRING(SS_LCTL("M"));
          SEND_STRING(SS_LCTL("v"));	  
      } 
      break;       



	
  }
  return true;
};


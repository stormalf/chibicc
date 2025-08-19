typedef struct {
  int dummy;
} HashTable;


// Static global variable should not be visible externally
static HashTable classes;
/* {{{ prop handler tables */
static HashTable dom_document_prop_handlers;
static HashTable dom_xml_document_prop_handlers;
static HashTable dom_abstract_base_document_prop_handlers;
static HashTable dom_documentfragment_prop_handlers;
static HashTable dom_modern_documentfragment_prop_handlers;
static HashTable dom_node_prop_handlers;
static HashTable dom_modern_node_prop_handlers;
static HashTable dom_entity_reference_prop_handlers;
static HashTable dom_modern_entity_reference_prop_handlers;
static HashTable dom_nodelist_prop_handlers;
static HashTable dom_namednodemap_prop_handlers;
static HashTable dom_characterdata_prop_handlers;
static HashTable dom_modern_characterdata_prop_handlers;
static HashTable dom_attr_prop_handlers;
static HashTable dom_modern_attr_prop_handlers;
static HashTable dom_element_prop_handlers;
static HashTable dom_modern_element_prop_handlers;
static HashTable dom_modern_element_prop_handlers;
static HashTable dom_text_prop_handlers;
static HashTable dom_modern_text_prop_handlers;
static HashTable dom_documenttype_prop_handlers;
static HashTable dom_modern_documenttype_prop_handlers;
static HashTable dom_notation_prop_handlers;
static HashTable dom_modern_notation_prop_handlers;
static HashTable dom_entity_prop_handlers;
static HashTable dom_modern_entity_prop_handlers;
static HashTable dom_processinginstruction_prop_handlers;
static HashTable dom_modern_processinginstruction_prop_handlers;
static HashTable dom_namespace_node_prop_handlers;
static HashTable dom_token_list_prop_handlers;

// Make sure the variable is used so it doesn't get optimized out
HashTable *get_dom_handlers(void) {
  return &dom_document_prop_handlers;
}

// Mock zend_extension struct, simplified
typedef struct {
    const char *name;
    const char *version;
    const char *author;
    const char *url;
    const char *copyright;
} zend_extension;

// Tentative definition: no initializer
static zend_extension opcache_extension_entry;

// Full initialized definition
static zend_extension opcache_extension_entry = {
    "OPcache",
    "8.0.0",
    "Zend Technologies",
    "http://www.zend.com/",
    "Copyright (c)"
};
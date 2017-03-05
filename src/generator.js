const codeGenerator = {
  table: {
    genTable(opts) {
      let code = '';
      const fieldFinitions = '  ' + codeGenerator.field.genFieldTypeDefinitions(opts.fields).join('\n  ');
      const tableDefinition = `struct {\n${fieldFinitions}\n} table; // ${opts.table.name}`;
      return tableDefinition;
    },
    genMethodDefinitions() {}
  },
  field: {
    typeToCPPType: {
      'timestamp': 'Field<TIMESTAMP, int64_t>',
      'dimension': 'Field<DIMENSION, string>',
      'metric.float': 'Field<METRIC_FLOAT, float>',
      'bool': 'Field<BOOL, bool>'
    },
    genFieldTypeDefinitions(fields) {
      const generated = [];
      for (var i = 0; i < fields.length; i++) {
        const field = fields[i];
        generated.push(codeGenerator.field.generateFieldDefinition(field));
      }
      return generated;
    },
    generateFieldDefinition(field) {
      return `${codeGenerator.field.typeToCPPType[field.type]} ${field.name};`;
    }
  }
};

console.log(codeGenerator.table.genTable({
  table: {
    name: 'pageviews'
  },
  fields: [
    {
      name: 'timestamp',
      type: 'timestamp'
    },
    {
      name: 'country',
      type: 'dimension'
    },
    {
      name: 'price',
      type: 'metric.float'
    }
  ]
}))

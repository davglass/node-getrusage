{
  'targets': [
    {
      'target_name': 'getrusage',
      'include_dirs': [
        "<!(node -e \"require('nan')\")"
      ],
      'sources': [
        'getrusage.cc'
      ]
    }
  ]
}

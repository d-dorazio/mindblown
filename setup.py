#!/usr/bin/env python
# -*- coding: utf-8 -*-

try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

description = '''
TODO
'''

requirements = [
    # TODO: put package requirements here
]

test_requirements = [
    # TODO: put package test requirements here
]

setup(
    name='brainpy',
    version='0.1.0',
    description="Simple Brainf*ck interpreter written in Python",
    long_description=description,
    author="Daniele D\'Orazio",
    author_email='d.dorazio96@gmail.com',
    url='https://github.com/d-dorazio/brainpy',
    packages=[
        'brainpy',
    ],
    package_dir={'brainpy': 'brainpy'},
    include_package_data=True,
    install_requires=requirements,
    license="MIT",
    zip_safe=False,
    keywords='brainpy',
    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Natural Language :: English',
        "Programming Language :: Python :: 2",
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
    ],
    test_suite='tests',
    tests_require=test_requirements)

import lit.formats
import os


config.name = 'RISCV_Decoder_Regression'

config.test_format = lit.formats.ShTest(False)

config.suffixes = ['.test']

config.test_source_root = os.path.dirname(__file__)

decoder_path = os.path.join(config.test_source_root, '..', 'decoder')
config.substitutions.append(('%decoder', decoder_path))